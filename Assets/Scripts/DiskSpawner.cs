using System.Collections.Generic;
using UnityEngine;

public class DiskSpawner : MonoBehaviour
{
    // Datas
    [SerializeField, Range(1, 32)]
    private byte count = 3;

    private List<Disk> disks = new List<Disk>();
    public List<Disk> Disks => disks;

    // Prefabs
    [SerializeField]
    private Disk diskPrefab;

    // Other components
    [SerializeField]
    private Tower towerA;

    private void Start()
    {
        for (byte i = count; i > 0; i--)
        {
            Disk disk = Instantiate(diskPrefab, towerA.transform.position + Vector3.up * (count - i) * 1.5f, Quaternion.Euler(90f, 0f, 0f));

            if (disk != null)
            {
                disk.Order = i;

                towerA.Push(disk, true);
                disks.Add(disk);
            }
        }
    }
}
