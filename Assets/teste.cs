using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;

public class teste : MonoBehaviour
{

    // [DllImport("libTeste_lib", CallingConvention = CallingConvention.Cdecl)]
    // private static extern bool CreateFile ();
    // [DllImport("libTeste_lib", CallingConvention = CallingConvention.Cdecl)]
    // private static extern int CreateSphere ();
    [DllImport("libTeste_lib", EntryPoint = "getPC", CallingConvention = CallingConvention.Cdecl)]
    private static extern int getPC ();
    

    // Start is called before the first frame update
    void Start()
    {
        // print("Function getPC() started!");
        Debug.Log(getPC());
        // print("Ended!!");
        // print("Function CreateSphere() started!");
        // Debug.Log(CreateSphere());
        // print(CreateFile());

        // GameObject Model = (GameObject)Resources.Load("model");
        // GameObject Model = (GameObject)Resources.Load("sensor_data");
        // Instantiate(Model);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}

// Angulos estão em radianos
// Distâncias estão em metros
// Usar Quaternion para as rotações