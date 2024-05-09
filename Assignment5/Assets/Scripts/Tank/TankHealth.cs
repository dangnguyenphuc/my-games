using UnityEngine;
using UnityEngine.UI;
using Unity.Netcode;

public class TankHealth : NetworkBehaviour
{
    public float m_StartingHealth = 100f;       
    public float m_StartingEnergy = 100f;     
    public Slider m_HealthBar;                        
    public Image m_HealthFillImage;
    public Slider m_EnergyBar;                        
    public Image m_EnergyFillImage;                      
    public Color m_FullHealthColor = Color.green;  
    public Color m_ZeroHealthColor = Color.red;    
    public Color m_FullEnergyColor = Color.blue;  
    public Color m_ZeroEnergyColor = Color.gray;   
    public GameObject m_ExplosionPrefab;
    
    private AudioSource m_ExplosionAudio;          
    private ParticleSystem m_ExplosionParticles;   
    private bool m_Dead;            

    public NetworkVariable<float> Health = new NetworkVariable<float>(100);
    public NetworkVariable<int> Energy = new NetworkVariable<int>(100);
    public NetworkVariable<float> SpeedBuffTimer = new NetworkVariable<float>(0f);

    float m_EnergyTimer = 0;
    bool m_IsBuffed;

    private void Awake()
    {
        m_ExplosionParticles = Instantiate(m_ExplosionPrefab).GetComponent<ParticleSystem>();
        m_ExplosionAudio = m_ExplosionParticles.GetComponent<AudioSource>();

        m_ExplosionParticles.gameObject.SetActive(false);
    }

    public override void OnNetworkSpawn()
    {
        Energy.OnValueChanged += OnEnergyChanged;
        Health.OnValueChanged += OnHealthChanged;
        OnEnergyChanged(0, Energy.Value);
        OnHealthChanged(0, Health.Value);
    }

    public override void OnNetworkDespawn()
    {
        Energy.OnValueChanged -= OnEnergyChanged;
        Health.OnValueChanged -= OnHealthChanged;
    }

    void OnEnergyChanged(int previousValue, int newValue)
    {
        SetEnergyBarValue(newValue);
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
          UpdateHealthClientRpc();
        }
    }

    void SetHealthBarValue(float healthBarValue)
    {
        m_HealthBar.value = healthBarValue;
        m_HealthFillImage.color = Color.Lerp (m_ZeroHealthColor, m_FullHealthColor, healthBarValue/m_StartingHealth);
    }

    void SetEnergyBarValue(int resourceBarValue)
    {
        m_EnergyBar.value = resourceBarValue;
        m_EnergyFillImage.color = Color.Lerp (m_ZeroEnergyColor, m_FullEnergyColor, resourceBarValue/m_StartingEnergy);
    }


    private void OnDeath()
    {
        // Play the effects for the death of the tank and deactivate it.
        m_Dead = true;

        m_ExplosionParticles.transform.position = transform.position;
        m_ExplosionParticles.gameObject.SetActive (true);

        m_ExplosionParticles.Play ();

        // m_ExplosionAudio.Play ();

        gameObject.SetActive (false);
    }

    [ClientRpc]
    private void UpdateHealthClientRpc(){
        OnDeath ();
    }

    void Update()
    {
        if (IsServer)
        {
            UpdateServer();
        }
    }

    void UpdateServer()
    {
        // energy regen
        if (m_EnergyTimer < NetworkManager.ServerTime.TimeAsFloat)
        {
            if (Energy.Value < 100)
            {
                if (Energy.Value + 5 > 100)
                {
                    Energy.Value = 100;
                }
                else
                {
                    Energy.Value += 5;
                }
            }

            m_EnergyTimer = NetworkManager.ServerTime.TimeAsFloat + 1;
        }
    }

    public void AddBuff(Buff.BuffType buff)
    {
        if (buff == Buff.BuffType.Health)
        {
            Health.Value += 20;
            if (Health.Value >= 100)
            {
                Health.Value = 100;
            }
        }

        if (buff == Buff.BuffType.Energy)
        {
            Energy.Value += 50;
            if (Energy.Value >= 100)
            {
                Energy.Value = 100;
            }
        }
    }

}
