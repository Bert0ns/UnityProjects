using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.InputSystem;
using Unity.VisualScripting;
using UnityEngine.UI;

public class GameManager : MonoBehaviour
{
    public static GameManager Instance;

    public event EventHandler OnPausePerformed;
    public event EventHandler OnGameEnded;

    private CustomInputs input;

    private int P1_points = 0;
    private int P2_points = 0;

    [SerializeField] private float gameTime = 180f;
    private float gameTimer;
    [SerializeField] private TextMeshProUGUI countdownTimerText;
    [SerializeField] private Image timerImage;

    [SerializeField] private TextMeshProUGUI p1_points_text;
    [SerializeField] private TextMeshProUGUI p2_points_text;

    [SerializeField] private GameObject pause_panel;
    private bool game_is_paused = false;
    private bool game_ended = false;
    [SerializeField] private GameObject win_panel;
    [SerializeField] private TextMeshProUGUI playerWinText;
    [SerializeField] private TextMeshProUGUI playerScoreText;

    private void Awake()
    {
        Instance = this;
        input = new CustomInputs();
    }
    private void Start()
    {
        Time.timeScale = 1f;
        game_ended = false;
        gameTimer = gameTime;

        Ball_P1.Instance.OnBall_P1CollisionP2 += Instance_OnBall_P1CollisionP2;
        Ball_P2.Instance.OnBall_P2CollisionP1 += Instance_OnBall_P2CollisionP1;
        

        pause_panel.SetActive(false);
        win_panel.SetActive(false);
    }
    private void Update()
    {
        if(gameTimer > 0)
        {
            gameTimer -= Time.deltaTime;

            TimerTextUpdate();

        }
        CheckGameState();
    }
    private void CheckGameState()
    {
        if(gameTimer <= 0)
        {
            EndGame();
        }
    }
    private void EndGame()
    {
        if(game_ended)
        {
            return;
        }
        game_ended = true;
        Time.timeScale = 0f;

        OnGameEnded?.Invoke(this, EventArgs.Empty);

        if (P1_points > P2_points)
        {
            playerWinText.text = "PLAYER RED WINS";
        }
        else if (P1_points < P2_points)
        {
            playerWinText.text = "PLAYER BLUE WINS";
        }
        else
        {
            playerWinText.text = "IT IS A TIE";
        }

        playerScoreText.text = P1_points.ToString() + "     " + P2_points.ToString();

        win_panel.SetActive(true);
    }
    private void TimerTextUpdate()
    {
        countdownTimerText.text = Convert.ToInt32(gameTimer).ToString();
        timerImage.fillAmount = gameTimer/gameTime;
    }
    private void Pause_performed(UnityEngine.InputSystem.InputAction.CallbackContext obj)
    {
        if (game_is_paused)
        {
            Game_Resume();
        }
        else
        {
            Pause_menu_activate();
        }
    }

    private void Pause_menu_activate()
    {
        Time.timeScale = 0f;
        pause_panel.SetActive(true);
        game_is_paused = true;

        OnPausePerformed?.Invoke(this, EventArgs.Empty);
    }

    private void Instance_OnBall_P2CollisionP1(object sender, EventArgs e)
    {
        P2_points++;
        p2_points_text.text = P2_points.ToString(); 
    }

    private void Instance_OnBall_P1CollisionP2(object sender, EventArgs e)
    {
        P1_points++;
        p1_points_text.text = P1_points.ToString();
    }

    public void Game_Restart()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
    }

    public void Game_Resume()
    {
        Time.timeScale = 1f;
        pause_panel.gameObject.SetActive(false);
        game_is_paused = false;

        OnPausePerformed?.Invoke(this, EventArgs.Empty);
    }

    public void Game_Quit()
    {
        Application.Quit();
    }

    private void OnEnable()
    {
        input.Enable();
        input.Game.Pause.performed += Pause_performed;
    }
    private void OnDisable()
    {
        input.Disable();
        input.Game.Pause.performed -= Pause_performed;
    }
}
