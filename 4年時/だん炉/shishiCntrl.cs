using UnityEngine;
using System.Collections;

public class shishiCntrl : MonoBehaviour {
	/*
	// debug
	private bool bHaikei = true;
	private bool bParticle = true;
	private bool bShishi = true;

	public GameObject haikei;
	public GameObject particle;
	public GameObject shishi;*/

	public GameObject BackGroudShishi;
	public GameObject shishiodoshi;
	public GameObject DayLightManager;
	public GameObject NightLightManager;
	public Sprite DayShishiTex;
	public Sprite NightShishiTex;

	public float TorqPow;
	private int torqueCnt;
	private SpriteRenderer ShishiSprite;

	private Camera mainCamera;
	private short daytime;
	private const short day = 0;
	private const short night = 1;
	public Material matDaySky;
	public Material matNightSky;
	public GameObject hotarunohikari;

	// Use this for initialization
	void Start () {
		ShishiSprite = BackGroudShishi.GetComponent<SpriteRenderer>();
		torqueCnt = 0;
		mainCamera = Camera.main;

		int nowTime = System.DateTime.Now.Hour;
		if(( nowTime >= 4 ) &&
		   ( nowTime <= 18 ))
		{
			daytime = day;
		}
		else
		{
			daytime = night;
		}
		ChangeDaytime( daytime );
	}
	
	// Update is called once per frame
	void Update () {

		// change daytime
		if( Input.GetKeyUp( KeyCode.UpArrow ))
		{
			//bParticle = !bParticle;
			//particle.SetActive( bParticle );

			daytime ++;
			if( daytime > night )
			{
				daytime = day;
			}
			ChangeDaytime( daytime );
		}
		if( Input.GetKeyUp( KeyCode.DownArrow ))
		{
			//bHaikei = !bHaikei;
			//haikei.SetActive( bHaikei );

			daytime --;
			if( daytime < day )
			{
				daytime = night;
			}
			ChangeDaytime( daytime );
		}

		// SpinBamboo
		if( Input.GetKeyUp( KeyCode.Space ) || Input.GetKeyUp( KeyCode.LeftArrow ))
		{
			//bShishi = !bShishi;
			//shishi.SetActive( bShishi );

			torqueCnt ++;
		}


		if( torqueCnt > 0 )
		{
			shishiodoshi.rigidbody.AddTorque ( new Vector3( 0, 0, TorqPow ));
			torqueCnt++;
			if( torqueCnt > 15 )
			{
				torqueCnt = 0;
			}
		}
	}

	void ChangeDaytime( int daytime )
	{
		Skybox skybox;
		skybox = mainCamera.GetComponent<Skybox>();
		
		AudioSource[] audio;
		audio = GetComponents<AudioSource>();

		if( daytime == day )
		{
			skybox.material = matDaySky;
			hotarunohikari.SetActive( false );
			NightLightManager.SetActive( false );
			DayLightManager.SetActive( true );
			ShishiSprite.sprite = DayShishiTex;
			audio[1].Stop();
		}
		else if( daytime == night )
		{
			skybox.material = matNightSky;
			hotarunohikari.SetActive( true );
			NightLightManager.SetActive( true );
			DayLightManager.SetActive( false );
			ShishiSprite.sprite = NightShishiTex;
			audio[1].Play();
		}
	}
}
