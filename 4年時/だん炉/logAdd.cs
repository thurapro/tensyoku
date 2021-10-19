using UnityEngine;
using System.Collections;

public class logAdd : MonoBehaviour {

    public GameObject m_Log;

	// Use this for initialization
	void Start () {
	    
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    public void Entry()
    {
        Instantiate(m_Log);
    }
}
