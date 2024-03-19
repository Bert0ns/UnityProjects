using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AudioManager : MonoBehaviour
{
    public static AudioManager Instance;

    [SerializeField] private AudioSource as_background;
    [SerializeField] private AudioSource as_sfx;

    [SerializeField] private AudioClip backgroundMusic;
    [SerializeField] private AudioClip ball_P1_Bounce;
    [SerializeField] private AudioClip ball_P2_Bounce;
    [SerializeField] private AudioClip player1_point;
    [SerializeField] private AudioClip player2_point;
    [SerializeField] private AudioClip pause;
    [SerializeField] private AudioClip player_invisible;
    [SerializeField] private AudioClip win_sfx;
    private void Awake()
    {
        Instance = this;
    }
    private void Start()
    {
        PlayBackgroungMusic();

        Ball_P1.Instance.OnBall_P1Collision += Instance_OnBall_P1Collision;
        Ball_P1.Instance.OnBall_P1CollisionP2 += Instance_OnBall_P1CollisionP2;
        Ball_P2.Instance.OnBall_P2Collision += Instance_OnBall_P2Collision;
        Ball_P2.Instance.OnBall_P2CollisionP1 += Instance_OnBall_P2CollisionP1;
        GameManager.Instance.OnPausePerformed += Instance_OnPausePerformed;
        GameManager.Instance.OnGameEnded += Instance_OnGameEnded;

        Player_Invisibility.OnPlayerInvisible += Player_Invisibility_OnPlayerInvisible;
    }

    private void Instance_OnGameEnded(object sender, EventArgs e)
    {
        as_sfx.clip = win_sfx;
        as_sfx.pitch = 1f;
        as_sfx.Play();
    }


    /*
     * We don't know why logging the as_sfx call fixes it being null
     * nor do we know who calls the function a second time
     * but everything works on the second try so we called it a day
     */
    private void Player_Invisibility_OnPlayerInvisible(object sender, EventArgs e)
    {
        if(as_sfx == null)
        {
            Debug.Log("as_sfx called");
            return; 
        }
        as_sfx.clip = player_invisible;
        as_sfx.pitch = 2f;
        as_sfx.Play();
    }

    private void Instance_OnPausePerformed(object sender, EventArgs e)
    {
        as_sfx.clip = pause;
        as_sfx.pitch = 2.25f;
        as_sfx.Play();
    }

    private void Instance_OnBall_P2CollisionP1(object sender, EventArgs e)
    {
        as_sfx.clip = player2_point;
        as_sfx.pitch = 2.25f;
        as_sfx.Play();
    }

    private void Instance_OnBall_P1CollisionP2(object sender, EventArgs e)
    {
        as_sfx.clip = player1_point;
        as_sfx.pitch = 2.25f;
        as_sfx.Play();
    }

    private void PlayBackgroungMusic()
    {
        as_background.clip = backgroundMusic;
        as_background.Play();
    }
    private void Instance_OnBall_P2Collision(object sender, EventArgs e)
    {
        as_sfx.clip = ball_P2_Bounce;
        as_sfx.pitch = 2.25f;
        as_sfx.Play();
    }

    private void Instance_OnBall_P1Collision(object sender, EventArgs e)
    {
        as_sfx.clip = ball_P1_Bounce;
        as_sfx.pitch = 2.25f;
        as_sfx.Play();
    }
}
