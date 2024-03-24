using UnityEngine;

public class CameraManager : MonoBehaviour
{
    [SerializeField]
    private float moveSpeed;
    [SerializeField]
    private float limitRotateX;

    private float currentXRotation;
    private float currentYRotation;

    private void Awake()
    {
        Cursor.visible = false;
        Cursor.lockState = CursorLockMode.Locked;
    }

    private void Update()
    {
        Move();
        Rotate();
    }

    private void Move()
    {
        float x = Input.GetAxisRaw("Horizontal");
        float z = Input.GetAxisRaw("Vertical");

        transform.position += (transform.right * x + transform.forward * z).normalized * moveSpeed * Time.deltaTime;
    }

    private void Rotate()
    {
        float x = -Input.GetAxisRaw("Mouse Y");
        float y = Input.GetAxisRaw("Mouse X");

        currentXRotation += x;
        currentYRotation += y;

        currentXRotation = Mathf.Clamp(currentXRotation, -limitRotateX, limitRotateX);

        transform.localEulerAngles = new Vector3(currentXRotation, currentYRotation, 0f);
    }
}
