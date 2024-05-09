using UnityEngine;
using Unity.Netcode;

public class ShellExplosion : NetworkBehaviour
{
    public LayerMask m_TankMask;
    public ParticleSystem m_ExplosionParticles;       
    public AudioSource m_ExplosionAudio;              
    public float m_MaxDamage = 50f;                  
    public float m_ExplosionForce = 1000f;            
    public float m_MaxLifeTime = 2f;                  
    public float m_ExplosionRadius = 5f;

    private void Start()
    {
        Invoke(nameof(DestroyShell), m_MaxLifeTime);
        Destroy(gameObject, m_MaxLifeTime);
    }

    public void SetVelocity(Vector3 velocity)
    {
        if (IsServer)
        {
            var shell = GetComponent<Rigidbody>();
            shell.velocity = velocity;
            SetVelocityClientRpc(velocity);
        }
    }

    [ClientRpc]
    void SetVelocityClientRpc(Vector3 velocity)
    {
        if (!IsHost)
        {
            var shell = GetComponent<Rigidbody>();
            shell.velocity = velocity;
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (!NetworkManager.Singleton.IsServer || !NetworkObject.IsSpawned)
        {
            return;
        }

        // SetExplosionForceClientRpc();
        Collider[] colliders = Physics.OverlapSphere (transform.position, m_ExplosionRadius, m_TankMask);

        for (int i = 0; i < colliders.Length; i++)
        {
          Rigidbody targetRigidbody = colliders[i].GetComponent<Rigidbody>();

          if (!targetRigidbody)
          {
            continue;
          }

          // targetRigidbody.AddExplosionForce (m_ExplosionForce, transform.position, m_ExplosionRadius);
          TankHealth targetHealth = targetRigidbody.GetComponent<TankHealth>();
          HeavyTankAI aiHealth = targetRigidbody.GetComponent<HeavyTankAI>();
          if (!targetHealth && !aiHealth)
          {
            continue;
          }

          float dmg = CalculateDamage(targetRigidbody.position);

          if (!aiHealth)
          { 
              targetRigidbody.AddExplosionForce (m_ExplosionForce, transform.position, m_ExplosionRadius);
              targetHealth.TakeDamage(dmg);
          }

          if (!targetHealth)
          {
              targetRigidbody.AddExplosionForce (m_ExplosionForce/10, transform.position, m_ExplosionRadius);
              aiHealth.TakeDamage(dmg);
          }
          
        }

        SetExplosionForceClientRpc();

        DestroyShell();
        Destroy(gameObject);
      }


    private float CalculateDamage(Vector3 targetPosition)
    {
        // Calculate the amount of damage a target should take based on it's position.
        Vector3 explosionToTarget = targetPosition - transform.position;

        float explosionDistance = explosionToTarget.magnitude;

        float relativeDistance = (m_ExplosionRadius - explosionDistance) / m_ExplosionRadius;

        float damage = relativeDistance * m_MaxDamage;

        damage = Mathf.Max (0.0f, damage);
        return damage;
    }

    private void DestroyShell()
    {
        if (!NetworkObject.IsSpawned)
        {
            return;
        }

        NetworkObject.Despawn(true);
    }

    [ClientRpc]
    private void SetExplosionForceClientRpc()
    {
        m_ExplosionParticles.transform.parent = null;
        m_ExplosionParticles.Play();

        Destroy(m_ExplosionParticles.gameObject, m_ExplosionParticles.duration);
    }

}
