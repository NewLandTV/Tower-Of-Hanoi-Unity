using System.Collections.Generic;
using UnityEngine;

public class Tower : MonoBehaviour
{
    // Datas
    [SerializeField]
    private ID id;

    private Stack<Disk> disks = new Stack<Disk>();
    public Stack<Disk> Disks => disks;

    public enum ID
    {
        A,
        B,
        C
    }

    public void Push(Disk disk, bool initialize = false)
    {
        if (disk == null)
        {
            return;
        }

        if (!initialize)
        {
            disk.transform.position = transform.position + Vector3.up * 3f;

            disk.gameObject.SetActive(true);
        }

        disks.Push(disk);
    }

    public Disk Pop()
    {
        if (!disks.TryPop(out Disk disk))
        {
            return null;
        }

        disk.gameObject.SetActive(false);

        return disk;
    }
}
