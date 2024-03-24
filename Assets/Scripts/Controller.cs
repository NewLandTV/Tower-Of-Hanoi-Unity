using UnityEngine;

public class Controller : MonoBehaviour
{
    // Datas
    [SerializeField]
    private Tower[] towers;

    private Disk selectedDisk;

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Alpha1))
        {
            SelectOrMoveDisk(Tower.ID.A);
        }
        if (Input.GetKeyDown(KeyCode.Alpha2))
        {
            SelectOrMoveDisk(Tower.ID.B);
        }
        if (Input.GetKeyDown(KeyCode.Alpha3))
        {
            SelectOrMoveDisk(Tower.ID.C);
        }
    }
    
    private void SelectOrMoveDisk(Tower.ID towerID)
    {
        if (selectedDisk == null)
        {
            Disk disk = towers[(int)towerID].Pop();

            if (disk == null)
            {
                return;
            }

            selectedDisk = disk;

            return;
        }

        if (towers[(int)towerID].Disks.TryPeek(out Disk result) && selectedDisk.Order > result.Order)
        {
            return;
        }

        towers[(int)towerID].Push(selectedDisk);

        selectedDisk = null;
    }
}
