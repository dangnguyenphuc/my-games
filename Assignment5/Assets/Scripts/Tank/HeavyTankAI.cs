using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Unity.Netcode;
using UnityEngine.AI;
using UnityEngine.UI;

public class HeavyTankAI : NetworkBehaviour
{
    public NavMeshAgent agent;

    public LayerMask m_GroundMask, m_TankMask;

    public float m_StartingHealth = 200f;
    public Slider m_HealthBar;                        
    public Image m_HealthFillImage;
    public Color m_FullHealthColor = Color.green;  
    public Color m_ZeroHealthColor = Color.red;
    public GameObject m_ExplosionPrefab;
    bool m_Dead;

    public NetworkVariable<float> Health = new NetworkVariable<float>(200);

    //Patroling
    public Vector3 walkPoint;
    bool walkPointSet;
    public float walkPointRange;

    //Attacking
    public float timeBetweenAttacks;
    bool alreadyAttacked;
    public Rigidbody m_Shell;            
    public Transform m_FireTransform;
    public float m_LaunchForce = 10f; 

    //States
    public float sightRange = 15;
    public float attackRange = 10;
    public bool playerInSightRange, playerInAttackRange;

    private ParticleSystem m_ExplosionParticles;  

    private void Awake()
    {
        agent = GetComponent<NavMeshAgent>();
        m_Dead = false;

        m_ExplosionParticles = Instantiate(m_ExplosionPrefab).GetComponent<ParticleSystem>();
        m_ExplosionParticles.gameObject.SetActive(false);
    }

    public override void OnNetworkSpawn()
    {
        Health.OnValueChanged += OnHealthChanged;
        OnHealthChanged(0, Health.Value);
    }

    public override void OnNetworkDespawn()
    {
        Health.OnValueChanged -= OnHealthChanged;
    }
    

    void OnHealthChanged(float previousValue, float newValue)
    {
        SetHealthBarValue(newValue);
    }

    public void TakeDamage(float amount)
    {
        Health.Value -= amount;

        if (Health.Value <= 0 && !m_Dead)
        {
          OnDeath ();
          UpdateHealthClientRpc ();
        }
    }

    private void OnDeath()
    {
        // Play the effects for the death of the tank and deactivate it.
        m_Dead = true;

        m_ExplosionParticles.transform.position = transform.position;
        m_ExplosionParticles.gameObject.SetActive (true);
        m_ExplosionParticles.Play ();

        gameObject.SetActive (false);
    }

    [ClientRpc]
    private void UpdateHealthClientRpc()
    {
        if (m_HealthBar.value <= 0 && !m_Dead)
        {
          OnDeath ();
        }
    }

    void SetHealthBarValue(float healthBarValue)
    {
        m_HealthBar.value = healthBarValue;
        m_HealthFillImage.color = Color.Lerp (m_ZeroHealthColor, m_FullHealthColor, healthBarValue/m_StartingHealth);
    }

    private void Update()
    {
        if (!IsServer || !NetworkObject.IsSpawned)
          return;

        Collider[] collidersInSightRange = Physics.OverlapSphere (transform.position, sightRange, m_TankMask);
        Collider[] collidersInAttackRange = Physics.OverlapSphere (transform.position, attackRange, m_TankMask);

        if (collidersInSightRange.Length > 1)
          playerInSightRange = true;
        else 
          playerInSightRange = false;

        if (collidersInAttackRange.Length > 1)
          playerInAttackRange = true;
        else 
          playerInAttackRange = false;

        if (!playerInSightRange && !playerInAttackRange)
        {
            Patroling();
        }
        
        if (playerInSightRange)
        {
            ChasePlayer(collidersInSightRange[1].gameObject.transform.position);
        }
        
        if (playerInAttackRange) 
          AttackPlayer(collidersInSightRange[1].gameObject);
    }

    private void Patroling()
    {
        if (!walkPointSet) SearchWalkPoint();

        if (walkPointSet)
            agent.SetDestination(walkPoint);
        Vector3 distanceToWalkPoint = transform.position - walkPoint;
        //Walkpoint reached
        if (distanceToWalkPoint.magnitude < 1f)
            walkPointSet = false;
    }

    private void SearchWalkPoint()
    {
        //Calculate random point in range
        float randomZ = Random.Range(-walkPointRange, walkPointRange);
        float randomX = Random.Range(-walkPointRange, walkPointRange);

        walkPoint = new Vector3(transform.position.x + randomX, transform.position.y, transform.position.z + randomZ);

        if (Physics.Raycast(walkPoint, -transform.up, 2f, m_GroundMask))
            walkPointSet = true;
    }

    private void ChasePlayer(Vector3 position)
    {
        agent.SetDestination(position);
    }

    private void AttackPlayer(GameObject player)
    {
        // //Make sure enemy doesn't move
        agent.SetDestination(transform.position);

        transform.LookAt(player.transform);

        if (!alreadyAttacked)
        {
            ///Attack code here
            Rigidbody shellInstance = Instantiate(m_Shell, m_FireTransform.position, m_FireTransform.rotation) as Rigidbody;
            shellInstance.GetComponent<NetworkObject>().Spawn(true);
            shellInstance.AddForce(m_LaunchForce * m_FireTransform.forward, ForceMode.Impulse);
            ///End of attack code

            alreadyAttacked = true;
            Invoke(nameof(ResetAttack), timeBetweenAttacks);
        }
    }

    private void ResetAttack()
    {
        alreadyAttacked = false;
    }


    private void DestroyEnemy()
    {
        Destroy(gameObject);
    }
}
