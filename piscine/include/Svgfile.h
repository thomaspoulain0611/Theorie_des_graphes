#ifndef SVGFILE_H_INCLUDED
#define SVGFILE_H_INCLUDED
#include <set>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <windows.h>

extern HANDLE hConsole;
constexpr char defcol[] = "black";
class Svgfile
{
    public:

        Svgfile(std::string _filename = "output.svg", int _width=1000, int _height=800);
        ~Svgfile();
        void addText(double x, double y, std::string text, std::string color=defcol);
        void addLine(double x1, double y1, double x2, double y2, std::string color=defcol);
        void addDisk(double x, double y, double r, std::string color);
        static std::string makeRGB(int r, int g, int b);
        /// Type non copiable
        Svgfile(const Svgfile&) = delete;
        Svgfile& operator=(const Svgfile&) = delete;
        static bool s_verbose;

    private:
        std::string m_filename;
        std::ofstream m_ostrm;
        int m_width;
        int m_height;
        // Pour �viter les ouverture multiples
        static std::set<std::string> s_openfiles;
};
#endif // SVGFILE_H
