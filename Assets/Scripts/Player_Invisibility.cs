using System;
using UnityEngine;
using UnityEngine.UI;

public class Player_Invisibility : MonoBehaviour
{
    public static event EventHandler OnPlayerInvisible;

    private CustomInputs input;

    private PolygonCollider2D player_collider;
    private SpriteRenderer player_body;
    private Color newColor_body;
    private Color newColor_arm;

    [SerializeField]
    private int num_player = 1;
    [SerializeField]
    private float invisibility_timer_max = 1f;
    private float invisibility_timer = 0;
    [SerializeField]
    private float abilityCooldown_max = 3f;
    private float abilityCooldown = 0;

    [SerializeField]
    private float invisibilityAmount = 0.5f;
    private bool isInvisible = false;

    [SerializeField]
    private Image cooldown_bar;
    [SerializeField]
    private Image ability_bar;
    [SerializeField]
    private SpriteRenderer player_arm1;
    [SerializeField]
    private SpriteRenderer player_arm2;

    private void Awake()
    {
        input = new CustomInputs();
    }
    private void OnEnable()
    {
        input.Enable();
        switch (num_player)
        {
            case 2:
                //Player 2
                input.Player2.Invisibility.performed += Invisibility_performed;
                break;
            default:
                //Player 1
                input.Player.Invisibility.performed += Invisibility_performed;
                break;
        }
    }

    private void Invisibility_performed(UnityEngine.InputSystem.InputAction.CallbackContext obj)
    {
        Debug.Log("Tries to become invisible Player: " + num_player);
        if(invisibility_timer <= 0f && abilityCooldown <= 0f)
        {
            OnPlayerInvisible?.Invoke(this, EventArgs.Empty);

            ToggleInvisibilityPlayer();
            abilityCooldown = abilityCooldown_max;
            Debug.Log("Toggled invisibility of Player: " + num_player);
        }
    }

    private void OnDisable()
    {
        switch (num_player)
        {
            case 2:
                //Player 2
                input.Player2.Invisibility.performed -= Invisibility_performed;
                break;
            default:
                //Player 1
                input.Player.Invisibility.performed -= Invisibility_performed;
                break;
        }
        input.Disable();
    }
    void Start()
    {
        //rb = GetComponent<Rigidbody2D>();
        player_collider = GetComponent<PolygonCollider2D>();
        player_body = GetComponent<SpriteRenderer>();

        newColor_body = player_body.color;

        newColor_arm = player_arm1.color;
    }

    private void Update()
    {
        if(invisibility_timer > 0f)
        {
            invisibility_timer -= Time.deltaTime;
            float val = invisibility_timer / invisibility_timer_max;
            ability_bar.fillAmount = val;

            if(invisibility_timer <= 0f ) 
            {
                ToggleInvisibilityPlayer();

                ability_bar.fillAmount = 1f;
            }
        }

        if(abilityCooldown > 0f)
        {
            abilityCooldown -= Time.deltaTime;

            float val = abilityCooldown / abilityCooldown_max;

            cooldown_bar.fillAmount = val;     
        }
        else
        {
            cooldown_bar.fillAmount = 1f;
        }
    }

    private void ToggleInvisibilityPlayer()
    {
        isInvisible = !isInvisible;
        if (isInvisible)
        {
            invisibility_timer = invisibility_timer_max;

            newColor_body.a = invisibilityAmount;
            newColor_arm.a = invisibilityAmount;
        }
        else
        {
            newColor_body.a = 1f;
            newColor_arm.a = 1f;
        }
        player_collider.enabled = !player_collider.enabled;

        player_body.color = newColor_body;
        player_arm1.color = newColor_arm;
        player_arm2.color = newColor_arm;
    }
}
