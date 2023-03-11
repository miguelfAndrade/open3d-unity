using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// using Unity.IO.LowLevel.Unsafe;

[RequireComponent(typeof(MeshFilter))]
public class MeshGenerator : MonoBehaviour
{
    // FileHandle fileHandle;

    Mesh mesh;

    Vector3[] vertices;
    int[] triangles;

    // Start is called before the first frame update
    void Start()
    {
        mesh = new Mesh();
        GetComponent<MeshFilter>().mesh = mesh;
    }

    // // Update is called once per frame
    // void Update()
    // {
        
    // }

    // private void OnDrawGizmos() 
    // {
    //     if(vertices == null)
    //         return;

    //     for(int i = 0; iz vertices.Length; i++)
    //     {
    //         Gizmos.DrawSphere(vertices[i], 0.1f);
    //     }
    // }

    // private void ReadFile(string filePath)
    // {
    //     //string path = Path.Combine()
    // } 
}
