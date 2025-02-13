#pragma once

#include <string>
#include <memory>
#include <hpdf.h>
#include "resume.hpp"

class PDFGenerator {
public:
    PDFGenerator();
    ~PDFGenerator();

    // Generate PDF from Resume object
    bool generatePDF(const Resume& resume, const std::string& outputPath);

private:
    // PDF Generation helper methods
    void drawHeader(const Resume& resume, HPDF_Page page);
    void drawEducation(const Resume& resume, HPDF_Page page, float& yPosition);
    void drawExperience(const Resume& resume, HPDF_Page page, float& yPosition);
    void drawSkills(const Resume& resume, HPDF_Page page, float& yPosition);

    // Helper functions
    void drawText(HPDF_Page page, float x, float y, const std::string& text);
    void drawBoldText(HPDF_Page page, float x, float y, const std::string& text);
    float getTextWidth(HPDF_Page page, const std::string& text);
    
    // PDF document and fonts
    HPDF_Doc pdf;
    HPDF_Font defaultFont;
    HPDF_Font boldFont;

    // Page layout constants
    static constexpr float PAGE_WIDTH = 595.27f;  // A4 width in points
    static constexpr float PAGE_HEIGHT = 841.89f; // A4 height in points
    static constexpr float MARGIN = 50.0f;
    static constexpr float LINE_HEIGHT = 20.0f;
}; 