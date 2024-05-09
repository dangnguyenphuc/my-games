using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Unity.Netcode;

public class BuffCollider : NetworkBehaviour
{
    public LayerMask m_TankMask;
    public Buff.BuffType m_BuffType;

    private void Awake()
    {
        GetRandomBuffType();
        Invoke(nameof(DestroyBuff), 10f);
    }

    void GetRandomBuffType()
    {
        // Get the total number of BuffTypes
        int enumLength = System.Enum.GetNames(typeof(Buff.BuffType)).Length;

        // Generate a random index within the range of BuffTypes
        int randomIndex = Random.Range(0, enumLength);

        // Set the BuffType to the random index
        m_BuffType = (Buff.BuffType)randomIndex;
    }
    

    private void OnTriggerEnter(Collider other)
    {
        if (!NetworkManager.Singleton.IsServer || !NetworkObject.IsSpawned)
        {
            return;
        }
        SetTankBuffServerRpc();
      }

    [ServerRpc]
    private void SetTankBuffServerRpc()
    {
        // Find all the tanks in an area around the shell and damage them.
        Collider[] colliders = Physics.OverlapBox (gameObject.transform.position, transform.localScale / 2, Quaternion.identity, m_TankMask);

        for (int i = 0; i < colliders.Length; i++)
        {
          Rigidbody targetRigidbody = colliders[i].GetComponent<Rigidbody>();

          if (!targetRigidbody)
          {
            continue;
          }

          TankMovement targetMovement = targetRigidbody.GetComponent<TankMovement>();
          if (!targetMovement)
          {
            continue;
          }

          TankHealth targetHealth = targetRigidbody.GetComponent<TankHealth>();
          if (!targetHealth)
          {
            continue;
          }

          targetMovement.AddBuff(m_BuffType);
          targetHealth.AddBuff(m_BuffType);
          DestroyBuff ();
          Destroy(gameObject);
          break;
        }
    }

    public void DestroyBuff()
    {
        if (!NetworkObject.IsSpawned)
        {
            return;
        }
        NetworkObject.Despawn(true);
    }
}
