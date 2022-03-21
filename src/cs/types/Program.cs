// See https://aka.ms/new-console-template for more information

// Top level statements
var rect = new Rectangle(3.4f, 4.5f);
(float w, float h) = rect; // call Deconstructor
Console.WriteLine($"{w}, {h}");

// Object initializer
Bunny b1 = new Bunny {Name="Bo", LikesCarrots=true, LikesHumans=false};
Bunny b2 = new Bunny("Bo") {LikesHumans=false, LikesCarrots=true};

Console.WriteLine(b1);

Stock msft = new Stock();
msft.CurrentPrice = 30;
msft.CurrentPrice -= 3;
msft.SharesOwned = 10;
Console.WriteLine(msft.CurrentPrice);
Console.WriteLine(msft.Worth);
msft.Worth = 540;
Console.WriteLine($"{msft.Worth} {msft.SharesOwned}");


// indexer
Sentense s = new Sentense();
Console.WriteLine(s[3]);
s[3] = "kangaroo";
Console.WriteLine(s[3]);

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

public class Bunny
{
    public string Name;
    public bool LikesCarrots;
    public bool LikesHumans;

    public Bunny() { Name = ""; }
    public Bunny(string n) { Name = n; }
}

public class Panda
{
    public Panda Mate;

    public void Marry(Panda partner)
    {
        this.Mate = partner;
        partner.Mate = this;
    }
}

public class Stock
{
    decimal currentPrice; // private backing field
    decimal sharesOwned;

    public decimal CurrentPrice
    {
        get { return currentPrice; }
        set { currentPrice = value; }
    }

    public decimal SharesOwned
    {
        get { return sharesOwned; }
        set { sharesOwned = value; }
    }

    // read-only property
    // public decimal Worth
    // {
    //     get { return currentPrice * sharesOwned; }
    // }

    // public decimal Worth => currentPrice * sharesOwned;

    public decimal Worth
    {
        get => currentPrice * sharesOwned;
        set => sharesOwned = value / currentPrice;
    }
}

// Indexer
class Sentense
{
    string[] words;

    public Sentense(string s="The quick brown fox, jump over a lazy frog")
    {
        words = s.Split();
    }

    public string this [int wordNum] // indexer
    {
        get => words[wordNum];
        set => words[wordNum] = value;
    }
}