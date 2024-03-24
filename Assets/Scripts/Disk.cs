using UnityEngine;

public class Disk : MonoBehaviour
{
    private byte order;
    public byte Order
    {
        get => order;
        set
        {
            order = value;

            RecalculateSize();
        }
    }

    private void RecalculateSize()
    {
        transform.localScale = new Vector3(transform.localScale.x + 16f * (order + 1), transform.localScale.y + 16f * (order + 1), transform.localScale.z);
    }
}
