#pragma once
#include <vector>
#include <map>
#include <cstdint>
#include <string>
#include <iostream>
#include <fstream>

namespace olc
{
    enum COLOUR
    {
        FG_BLACK = 0x0000,
        FG_DARK_BLUE = 0x0001,
        FG_DARK_GREEN = 0x0002,
        FG_DARK_CYAN = 0x0003,
        FG_DARK_RED = 0x0004,
        FG_DARK_MAGENTA = 0x0005,
        FG_DARK_YELLOW = 0x0006,
        FG_GREY = 0x0007, // Thanks MS :-/
        FG_DARK_GREY = 0x0008,
        FG_BLUE = 0x0009,
        FG_GREEN = 0x000A,
        FG_CYAN = 0x000B,
        FG_RED = 0x000C,
        FG_MAGENTA = 0x000D,
        FG_YELLOW = 0x000E,
        FG_WHITE = 0x000F,
        BG_BLACK = 0x0000,
        BG_DARK_BLUE = 0x0010,
        BG_DARK_GREEN = 0x0020,
        BG_DARK_CYAN = 0x0030,
        BG_DARK_RED = 0x0040,
        BG_DARK_MAGENTA = 0x0050,
        BG_DARK_YELLOW = 0x0060,
        BG_GREY = 0x0070,
        BG_DARK_GREY = 0x0080,
        BG_BLUE = 0x0090,
        BG_GREEN = 0x00A0,
        BG_CYAN = 0x00B0,
        BG_RED = 0x00C0,
        BG_MAGENTA = 0x00D0,
        BG_YELLOW = 0x00E0,
        BG_WHITE = 0x00F0,
    };

    enum PIXEL_TYPE
    {
        PIXEL_SOLID = 0x2588,
        PIXEL_THREEQUARTERS = 0x2593,
        PIXEL_HALF = 0x2592,
        PIXEL_QUARTER = 0x2591,
    };

    class olcSprite
    {
    public:
        olcSprite()
        {
        }

        olcSprite(int w, int h)
        {
            Create(w, h);
        }

        olcSprite(std::wstring sFile)
        {
            if (!Load(sFile))
                Create(8, 8);
        }

        int nWidth = 0;
        int nHeight = 0;

    private:
        short *m_Glyphs = nullptr;
        short *m_Colours = nullptr;

        void Create(int w, int h)
        {
            nWidth = w;
            nHeight = h;
            m_Glyphs = new short[w * h];
            m_Colours = new short[w * h];
            for (int i = 0; i < w * h; i++)
            {
                m_Glyphs[i] = L' ';
                m_Colours[i] = FG_BLACK;
            }
        }

    public:
        void SetGlyph(int x, int y, short c)
        {
            if (x < 0 || x >= nWidth || y < 0 || y >= nHeight)
                return;
            else
                m_Glyphs[y * nWidth + x] = c;
        }

        void SetColour(int x, int y, short c)
        {
            if (x < 0 || x >= nWidth || y < 0 || y >= nHeight)
                return;
            else
                m_Colours[y * nWidth + x] = c;
        }

        short GetGlyph(int x, int y)
        {
            if (x < 0 || x >= nWidth || y < 0 || y >= nHeight)
                return L' ';
            else
                return m_Glyphs[y * nWidth + x];
        }

        short GetColour(int x, int y)
        {
            if (x < 0 || x >= nWidth || y < 0 || y >= nHeight)
                return FG_BLACK;
            else
                return m_Colours[y * nWidth + x];
        }

        short SampleGlyph(float x, float y)
        {
            int sx = (int)(x * (float)nWidth);
            int sy = (int)(y * (float)nHeight - 1.0f);
            if (sx < 0 || sx >= nWidth || sy < 0 || sy >= nHeight)
                return L' ';
            else
                return m_Glyphs[sy * nWidth + sx];
        }

        short SampleColour(float x, float y)
        {
            int sx = (int)(x * (float)nWidth);
            int sy = (int)(y * (float)nHeight - 1.0f);
            if (sx < 0 || sx >= nWidth || sy < 0 || sy >= nHeight)
                return FG_BLACK;
            else
                return m_Colours[sy * nWidth + sx];
        }

        bool Save(std::wstring sFile)
        {
            FILE *f = nullptr;
            _wfopen_s(&f, sFile.c_str(), L"wb");
            if (f == nullptr)
                return false;

            fwrite(&nWidth, sizeof(int), 1, f);
            fwrite(&nHeight, sizeof(int), 1, f);
            fwrite(m_Colours, sizeof(short), nWidth * nHeight, f);
            fwrite(m_Glyphs, sizeof(short), nWidth * nHeight, f);

            fclose(f);

            return true;
        }

        bool Load(std::wstring sFile)
        {
            delete[] m_Glyphs;
            delete[] m_Colours;
            nWidth = 0;
            nHeight = 0;

            FILE *f = nullptr;
            _wfopen_s(&f, sFile.c_str(), L"rb");
            if (f == nullptr)
                return false;

            std::fread(&nWidth, sizeof(int), 1, f);
            std::fread(&nHeight, sizeof(int), 1, f);

            Create(nWidth, nHeight);

            std::fread(m_Colours, sizeof(short), nWidth * nHeight, f);
            std::fread(m_Glyphs, sizeof(short), nWidth * nHeight, f);

            std::fclose(f);
            return true;
        }
    };

}