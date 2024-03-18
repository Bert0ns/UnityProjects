using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class PlayerMovement : MonoBehaviour
{
    private CustomInputs input = null;
    private Vector2 movVector = Vector2.zero;

    private Rigidbody2D rb = null;
    private Transform player_transform = null;
    [SerializeField]
    private int num_Player = 1;
    [SerializeField]
    private float movSpeed = 10f;
    [SerializeField]
    private float rotationSpeed = 720f;
    [SerializeField]
    private float dampeningFactorAngularVelocity = 0.95f;
    
    private void Awake()
    {
        input = new CustomInputs();
        rb = GetComponent<Rigidbody2D>();
        player_transform = GetComponent<Transform>();
    }
    private void FixedUpdate()
    {
        PlayerMoveDirection(rb, movVector, movSpeed);
        PlayerFaceDirection(rb, player_transform, movVector, rotationSpeed);
        PlayerAngularDirection(rb);
    }
    private void PlayerAngularDirection(Rigidbody2D rb)
    {
        if(rb.angularVelocity == 0)
        {
            return;
        }
        rb.angularVelocity = rb.angularVelocity * dampeningFactorAngularVelocity;
        if (rb.angularVelocity < 0.07)
        {
            rb.angularVelocity = 0f;
        }
    }
    private void PlayerMoveDirection(Rigidbody2D rb, Vector2 movVector, float movSpeed)
    {
        rb.velocity = movVector * movSpeed;
    }
    private void PlayerFaceDirection(Rigidbody2D rb, Transform player_transform, Vector2 direction, float rotation_speed)
    {
        if(direction == Vector2.zero)
        {
            return;
        }
        
        Quaternion targetRotation = Quaternion.LookRotation(player_transform.forward, direction);
        Quaternion rotation = Quaternion.RotateTowards(player_transform.rotation, targetRotation, rotation_speed * Time.deltaTime);

        rb.MoveRotation(rotation);
    }

    private void OnEnable()
    {
        input.Enable();
        switch (num_Player)
        {
            case 2:
                //Player 2
                input.Player2.Movement.performed += OnMovPerformed;
                input.Player2.Movement.canceled += OnMovCancelled;
                break;
            default:
                //Player 1
                input.Player.Movement.performed += OnMovPerformed;
                input.Player.Movement.canceled += OnMovCancelled;
                break;
        }
    }
    private void OnDisable()
    {
        //GameManager.Input.Disable();
        input.Player.Movement.performed -= OnMovPerformed;
        input.Player.Movement.canceled -= OnMovCancelled;
    }
    private void OnMovPerformed(InputAction.CallbackContext value)
    {
        movVector = value.ReadValue<Vector2>();
    }
    private void OnMovCancelled(InputAction.CallbackContext value)
    {
        movVector = Vector2.zero;
    }
}
