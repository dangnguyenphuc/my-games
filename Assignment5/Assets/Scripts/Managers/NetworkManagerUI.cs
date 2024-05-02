using System.Collections;
using System.Collections.Generic;
using Unity.Netcode;
using UnityEngine;
using UnityEngine.UI;

public class Network : MonoBehaviour
{
  public Button m_serverButton;
  public Button m_hostButton;
  public Button m_clientButton;

  private void Awake(){
    m_serverButton.onClick.AddListener( () => {
      NetworkManager.Singleton.StartServer();
    });

    m_hostButton.onClick.AddListener( () => {
      NetworkManager.Singleton.StartHost();
    });

    m_clientButton.onClick.AddListener( () => {
      NetworkManager.Singleton.StartClient();
    });
  }
}
