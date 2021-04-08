using System.Collections.Generic;
using UnityEngine;

namespace Unity.FPS.Game
{
    public class ActorsManager : MonoBehaviour
    {
        public List<Actor> Actors { get; private set; }
        public GameObject Player { get; private set; }

        public void SetPlayer(GameObject player) => Player = player; //匿名函数 =>

        void Awake()
        {
            Actors = new List<Actor>();
        }
    }
}
