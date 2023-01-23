using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;

public class teste : MonoBehaviour
{
    [DllImport("libTeste_lib")]
    // private static extern bool CreateFile ();
    private static extern bool pointCloud ();

    // Start is called before the first frame update
    void Start()
    {
        // print("Function pointCloud() started!");
        // print(pointCloud());
        // print("Function CreateFile() started!");
        // print(CreateFile());

        // GameObject Model = (GameObject)Resources.Load("model");
        GameObject Model = (GameObject)Resources.Load("sensor_data");
        Instantiate(Model);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}

// Angulos estão em radianos
// Distâncias estão em metros
// Usar Quaternion para as rotações