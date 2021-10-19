using UnityEngine;
using System.Collections;

public class ColSounds : MonoBehaviour {

	private int colCount;
	private float oldTime;
	private float currentTime;

	// Use this for initialization
	void Start () {
		colCount = 0;
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	void OnCollisionEnter()
	{
		currentTime = Time.time;
		if( currentTime - oldTime >= 2.0f )
		{
			colCount = 0;
		}

		colCount++;

		if( colCount <= 2 )
		{
			if( colCount == 1 )
			{
				oldTime = Time.time;
			}

			this.audio.Stop();
			this.audio.Play();
		}
	}
}
