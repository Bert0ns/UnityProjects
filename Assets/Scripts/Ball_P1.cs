using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Ball_P1 : MonoBehaviour
{
    public static Ball_P1 Instance;

    public event EventHandler OnBall_P1CollisionP2;
    public event EventHandler OnBall_P1Collision;
    private void Awake()
    {
        Instance = this;
    }

    [SerializeField] private float timerStart = 0.4f;
    private float timerCollisionPlayer;
    [SerializeField] private float timerBounceSound = 0.1f;
    private float timerSound;
    private void Update()
    {
        if(timerCollisionPlayer > 0)
        {
            timerCollisionPlayer -= Time.deltaTime;
        }
        if(timerSound > 0)
        {
            timerSound -= Time.deltaTime;
        }
    }
    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.collider.tag == "player2")
        {
            if(timerCollisionPlayer <= 0)
            {
                OnBall_P1CollisionP2?.Invoke(this, EventArgs.Empty);

                timerCollisionPlayer = timerStart;
            } 
        }
        else
        {
            PlayBounceSound();
        } 
    }

    private void PlayBounceSound()
    {
        if (timerSound <= 0)
        {
            OnBall_P1Collision?.Invoke(this, EventArgs.Empty);
            timerSound = timerBounceSound;
        }
    }
}
