using UnityEngine;
using System.Collections;

public class takiCntrl : MonoBehaviour {

    public waterFloat Log;
    private float LogAddTime;
    private float LogAddSpan = 20;

    private float KoiAddTime;
    private float KoiAddSpan = 2.1f;

	public GameObject DayLightManager;
	public GameObject NightLightManager;

    public Sprite m_TakiDayBG;
    public Sprite m_TakiNightBG;
    public SpriteRenderer m_TakiBGRend;

	private Camera mainCamera;
	private short daytime;
	private const short day = 0;
	private const short night = 1;
	public Material matDaySky;
	public Material matNightSky;

	// Use this for initialization
	void Start () {
		mainCamera = Camera.main;
		daytime = day;

		ChangeDaytime( day );
	}
	
	// Update is called once per frame
	void Update () {

        LogAddTime -= Time.deltaTime;
        KoiAddTime -= Time.deltaTime;

		// change daytime
		if( Input.GetKeyUp( KeyCode.UpArrow ))
		{
			daytime ++;
			if( daytime > night )
			{
				daytime = day;
			}
			ChangeDaytime( daytime );
		}
		if( Input.GetKeyUp( KeyCode.DownArrow ))
		{
			daytime --;
			if( daytime < day )
			{
				daytime = night;
			}
			ChangeDaytime( daytime );
		}

        //ŠÛ‘¾—¬‚µ
        if (Input.GetKeyDown(KeyCode.LeftArrow) && LogAddTime < 0 )
        {
            /* •Ç‚ ‚è—p
            Log.transform.position = new Vector3( -2.16f , 46 , 112 );
            Log.transform.localRotation = 
                Quaternion.Euler( new Vector3( 64 , 30*Random.value , 60*Random.value ) );
             * */

            //•Ç‚È‚µ—p
            Log.transform.position = new Vector3( -4.26f , 52.0f , 106.34f );
            Log.transform.localRotation = Quaternion.Euler(new Vector3( 43.39f , -8.481f , 15.03f ));
            //Log.rigidbody.velocity *= 0.0f;
            Log.rigidbody.AddForce(new Vector3(0, 0, 500));

            //‚±‚±‚Ü‚Å

            //Log.rigidbody.velocity *= 0.0f;
            //Log.rigidbody.angularVelocity *= 0.0f;
            Log.m_bSound = false;
            LogAddTime = LogAddSpan;
        }

        //ŒïoŒ»
        if (Input.GetKeyDown(KeyCode.RightArrow) && KoiAddTime < 0 )
        {
            GameObject Koi = (GameObject)Instantiate(Resources.Load("res_taki/koi") );
 
            Koi.transform.Translate( new Vector3( 
                    Random.Range( -4 , 4 ),
                    0,
                    Random.Range( -4 , 4 ) ) );

            KoiAddTime = KoiAddSpan;
        }

        //Debug.Log(KoiAddTime);
	}
	
	void ChangeDaytime( int daytime )
	{
		Skybox skybox;
		skybox = mainCamera.GetComponent<Skybox>();
		
		if( daytime == day )
		{
			skybox.material = matDaySky;
            m_TakiBGRend.sprite = m_TakiDayBG;
			DayLightManager.SetActive( true );
			NightLightManager.SetActive( false );
		}
		else if( daytime == night )
		{
			skybox.material = matNightSky;
            m_TakiBGRend.sprite = m_TakiNightBG;
			DayLightManager.SetActive( false );
			NightLightManager.SetActive( true );
		}
	}
}
