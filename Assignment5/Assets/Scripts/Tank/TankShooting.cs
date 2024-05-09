using UnityEngine;
using UnityEngine.UI;
using Unity.Netcode;

public class TankShooting : NetworkBehaviour
{
    public int m_PlayerNumber = 1;       
    public Rigidbody m_Shell;            
    public Transform m_FireTransform;    
    public Slider m_AimSlider;           
    public AudioSource m_ShootingAudio;  
    public AudioClip m_ChargingClip;     
    public AudioClip m_FireClip;         
    public float m_LaunchForce = 20f; 

    private string m_FireButton;         
    private float m_ChargeSpeed;                      


    private void OnEnable()
    {
        m_AimSlider.value = m_LaunchForce;
    }


    private void Start()
    {
        m_FireButton = "Fire";
    }

    private void Update()
    {
        if (!IsOwner) return;

        if(IsClient)
        {
            // Track the current state of the fire button and make decisions based on the current launch force.
            m_AimSlider.value = m_LaunchForce;

            if (Input.GetButtonDown(m_FireButton))
            {
              FireServerRpc();
            }
        }
    }

    private void Fire()
    {
        // Instantiate and launch the shell.
        Rigidbody shellInstance = Instantiate(m_Shell, m_FireTransform.position, m_FireTransform.rotation) as Rigidbody;
        
        shellInstance.GetComponent<NetworkObject>().SpawnWithOwnership(OwnerClientId);
        shellInstance.AddForce(m_LaunchForce * m_FireTransform.forward, ForceMode.Impulse);
        // shellInstance.AddForce(transform.up * m_LaunchForce, ForceMode.Impulse);
    }

    [ServerRpc(RequireOwnership=false)]
    public void FireServerRpc()
    {
        if (GetComponent<TankHealth>().Energy.Value >= 20)
        {
            Fire();

            GetComponent<TankHealth>().Energy.Value -= 20;
            if (GetComponent<TankHealth>().Energy.Value <= 0)
            {
                GetComponent<TankHealth>().Energy.Value = 0;
            }
        }
    }
}
