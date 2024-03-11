using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Ball_P2 : MonoBehaviour
{
    public static Ball_P2 Instance;

    public event EventHandler OnBall_P2CollisionP1;
    public event EventHandler OnBall_P2Collision;
    private void Awake()
    {
        Instance = this;
    }

    [SerializeField] private float timerStart = 0.4f;
    private float timer;
    [SerializeField] private float timerBounceSound = 0.1f;
    private float timerSound;
    private void Update()
    {
        if (timer > 0)
        {
            timer -= Time.deltaTime;
        }
        if (timerSound > 0)
        {
            timerSound -= Time.deltaTime;
        }
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.collider.tag == "player1" && timer <= 0)
        {
            OnBall_P2CollisionP1?.Invoke(this, EventArgs.Empty);

            timer = timerStart;
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
            OnBall_P2Collision?.Invoke(this, EventArgs.Empty);
            timerSound = timerBounceSound;
        }
    }
}
