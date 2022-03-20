// See https://aka.ms/new-console-template for more information

// Top level statements
var rect = new Rectangle(3.4f, 4.5f);
(float w, float h) = rect; // call Deconstructor
Console.WriteLine($"{w}, {h}");

class Rectangle
{
    public readonly float Width, Height;

    public Rectangle(float width, float height)
    {
        Width = width;
        Height = height;
    }

    public void Deconstruct(out float width, out float height)
    {
        width = Width;
        height = Height;
    }
}