using Snappy.Sharp;
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SnappySharp
{
    class Program
    {
        static void Main(string[] args)
        {
            var snappyDecompressor = new SnappyDecompressor();
            var baseDir = @"D:\Documents\Project\snappy-c\testdate\";
            var files = Directory.GetFiles(baseDir);
            foreach (var file in files)
            {
                using (var fileStream = File.OpenRead(file))
                using (var outStream = new FileStream(file.Replace(".snappy", ".txt"), FileMode.OpenOrCreate))
                {
                    var byteArr = new byte[fileStream.Length];
                    var compressSize = Convert.ToInt32(fileStream.Length);
                    fileStream.Read(byteArr, 0, compressSize);
                    var buf = snappyDecompressor.Decompress(byteArr, 0, compressSize);
                    outStream.Write(buf, 0, buf.Length);
                    outStream.Flush();
                }
            }
        }
    }
}
