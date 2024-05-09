using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Unity.Netcode;

public class BuffManager : NetworkBehaviour
{

    public Transform[] m_SpawnPoints;
    public GameObject m_BuffInstance;
    public float m_SpawnBuffTimerMax = 5f;
    public int m_MaxBuffNumber = 1;
    
    public static BuffManager Instance { get; private set; }

    private float m_SpawnBuffTimer;
    private List<GameObject> m_Buff;

    private void Awake() 
    {
        Instance = this;
        m_SpawnBuffTimer = m_SpawnBuffTimerMax;
        m_Buff = new List<GameObject>();
    } 

    private void Update() {
        if (!IsServer) {
            return;
        }

        m_SpawnBuffTimer -= Time.deltaTime;
        if (m_SpawnBuffTimer <= 0f) {
            m_SpawnBuffTimer = m_SpawnBuffTimerMax;

            if (m_Buff.Count >= m_MaxBuffNumber)
            {
                Destroy(m_Buff[0]);
                m_Buff.Remove(m_Buff[0]);
            }
            else if (m_Buff.Count < m_MaxBuffNumber) 
            {
                int buffIndex = UnityEngine.Random.Range(0, m_SpawnPoints.Length);
                Transform buffTransform = m_SpawnPoints[buffIndex];
                GameObject buff = Instantiate(m_BuffInstance, buffTransform.position, buffTransform.rotation);
                buff.GetComponent<NetworkObject>().SpawnWithOwnership(OwnerClientId);

                m_Buff.Add(buff);
            }
        }
    }
}
