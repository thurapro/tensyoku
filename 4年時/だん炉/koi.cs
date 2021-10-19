using UnityEngine;
using System.Collections;

public class koi : MonoBehaviour {

   // public Vector3 m_
    //public float m_UpForce = 1000; //上に向かう力
    public float m_fWaterHightY = -1.0f;
    private Vector3 m_TakituboPos;
    private Vector3 m_GoalPos;
    private Vector3 m_DustPos;
    private Vector3 m_LookAtPos;

    private bool m_bDeath = false;


	// Use this for initialization
	void Start () {

        //ゴールの位置をしゅとく　
        GameObject Goal = GameObject.Find("CarpRoot/CarpGoal");
        if (Goal)
        {
            m_GoalPos = Goal.transform.position;
        }

        //滝つぼの位置を取得
        GameObject Takitubo = GameObject.Find("CarpRoot/Takitubo");
        if (Takitubo)
        {
            m_TakituboPos = Takitubo.transform.position;
        }

        //当たると消える球の位置を取得
        GameObject Dust = GameObject.Find("CarpRoot/Dust");
        if (Dust)
        {
            m_DustPos = Dust.transform.position;
        }

	}
	
	// Update is called once per frame
	void Update () {

        //水面下に居たら浮力を与える
        float fDepth = m_fWaterHightY - transform.position.y ;
        if (fDepth > 0 && !m_bDeath)
        {
            rigidbody.AddForce(new Vector3(0, fDepth * 5.0f, 0));
        }

        if (transform.position.y < -20)
        {
            DestroyObject(gameObject);
        }

        if (!m_bDeath)
        {
            transform.LookAt(m_LookAtPos, new Vector3(0, 0, -1));
        }
        else
        {
            transform.LookAt(
                transform.position + rigidbody.velocity
                + new Vector3( 0 , 7 , 0 ) ,
                new Vector3(0, 0 , -1));

            rigidbody.AddForce( ( m_DustPos - transform.position).normalized*10 );
        }

	}

    void OnTriggerStay(Collider col)
    {
    
        //滝の中だったら上に向かう
        Vector3 GoalForce;
        if (col.gameObject.name == "CarpRoot")
        {
            GoalForce = (m_GoalPos - transform.position).normalized * 15;
        }
            //そうじゃなかったら滝つぼへ向かう
        else
        {
            GoalForce = (m_TakituboPos - transform.position).normalized;
        }
        rigidbody.AddForce(GoalForce);
        m_LookAtPos = m_GoalPos;
    }

    void OnTriggerEnter(Collider col)
    {
        //ゴールに入ったら
        if (col.gameObject.name == "CarpGoal")
        {
           // GetComponent<CapsuleCollider>().enabled = false;
            GetComponentInChildren<Animator>().SetBool("bJump", true);

            rigidbody.angularVelocity = new Vector3(0, 0, 0);
            rigidbody.AddForce(new Vector3(-120, 1200, 400) * Random.Range( 0.8f , 1.2f ) );
            rigidbody.useGravity = false;

            m_bDeath = true;
        }

        //削除球に入ったら
        if (col.gameObject.name == "Dust")
        {
            
            DestroyObject(gameObject);
        }
    }

}
