using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Unity.FPS.Game;
using UnityEngine.AI;
using UnityEngine.Events;

namespace Unity.FPS.AI
{
    public class TreeController : MonoBehaviour
    {
        //[Header("VFX")]
        //[Tooltip("当敌人死亡时，VFX预制就产生了")]
        public GameObject DeathVfx;

        //[Tooltip("死亡VFX产生的点")]
        public Transform DeathVfxSpawnPoint;

        Health m_Health;
        //[Tooltip("死亡后游戏对象被摧毁的延迟(允许动画)")]
        public float DeathDuration = 0f;
        EnemyManager m_EnemyManager;

        // Start is called before the first frame update
        void Start()
        {
            m_EnemyManager = FindObjectOfType<EnemyManager>();//返回场景中的所填类型的随机个体和集合

            m_Health = GetComponent<Health>();
            // Subscribe to damage & death actions
            m_Health.OnDie += OnDie;
            m_Health.OnDamaged += OnDamaged;
        }

        // Update is called once per frame
        void Update()
        {

        }


        void OnDie()
        {
            // spawn a particle system when dying
            //在死亡时生成粒子系统
            var vfx = Instantiate(DeathVfx, DeathVfxSpawnPoint.position, Quaternion.identity);
            Destroy(vfx, 5f);
     
            // this will call the OnDestroy function
            //这将调用OnDestroy函数
            Destroy(gameObject, DeathDuration);
        }


        void OnDamaged(float damage, GameObject damageSource)
        {

        }
    }
}
