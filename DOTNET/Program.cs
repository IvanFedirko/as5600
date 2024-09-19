using System;
using System.Device.I2c;

Console.WriteLine("Test AS5600");
//Slave address 0x36
I2cDevice i2c = I2cDevice.Create(new I2cConnectionSettings(1, 0x36));
double mult = 360d/4095d;
while (true)
{

    i2c.WriteByte(0x0E);
    var a11_8 = i2c.ReadByte();
    i2c.WriteByte(0x0F);
    var a7_0 = i2c.ReadByte();
    var angle = (a7_0) + (a11_8 << 8);

    //  360/4095 * angle
    Console.WriteLine($"Angle: {Math.Round(mult * angle, 1)}");
    System.Threading.Thread.Sleep(100);
}