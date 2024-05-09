using System;
using System.Collections;
using System.Collections.Generic;
using Unity.Netcode;
using UnityEngine;
using Random = UnityEngine.Random;

[RequireComponent(typeof(NetworkManager))]
public class TankSpawner : MonoBehaviour
{
    
    [SerializeField]
    CameraControl m_CameraControl;

    NetworkManager m_NetworkManager;

    int m_RoundRobinIndex = 0;
    
    [SerializeField]
    List<Transform> m_SpawnPositions = new List<Transform>() {};

    [SerializeField]
    List<Color> m_Colors = new List<Color>() {
      Color.blue,
      Color.red
    };

    /// <summary>
    /// Get a spawn position for a spawned object based on the spawn method.
    /// </summary>
    /// <returns>?The spawn position.</returns>
    /// <exception cref="NotImplementedException"></exception>
    public Transform GetNextSpawnPosition()
    {   
        m_RoundRobinIndex = (m_RoundRobinIndex + 1) % m_SpawnPositions.Count;
        return m_SpawnPositions[m_RoundRobinIndex];
    }

    public Color GetNextSpawnColor()
    {   
        return m_Colors[m_RoundRobinIndex];
    }
    
    private void Awake()
    {
        m_NetworkManager = gameObject.GetComponent<NetworkManager>();
        m_NetworkManager.ConnectionApprovalCallback += ConnectionApprovalWithRandomSpawnPos;
        m_NetworkManager.OnClientConnectedCallback += OnClientConnected;
    }

    void ConnectionApprovalWithRandomSpawnPos(NetworkManager.ConnectionApprovalRequest request, NetworkManager.ConnectionApprovalResponse response)
    {
        // Here we are only using ConnectionApproval to set the player's spawn position. Connections are always approved.
        response.CreatePlayerObject = true;
        Transform tempTransform = GetNextSpawnPosition();
        response.Position = tempTransform.position;
        response.Rotation = tempTransform.rotation;
        response.Approved = true;
        Debug.Log(response);
    }

    private void OnClientConnected(ulong clientId)
    {

        if ((NetworkManager.Singleton.IsServer && clientId != NetworkManager.ServerClientId))
        {
            return;
        }

        NetworkObject currentPlayer = m_NetworkManager.SpawnManager.GetPlayerNetworkObject(clientId);

        if (currentPlayer != null)
        {
            // Set the camera target to the transform of the current player
            m_CameraControl.m_Target = currentPlayer.transform;
        }
        else
        {
            Debug.LogError("Current player not found.");
        }
    }
}
