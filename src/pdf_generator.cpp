#include "pdf_generator.hpp"
#include <stdexcept>

PDFGenerator::PDFGenerator() {
    pdf = HPDF_New(nullptr, nullptr);
    if (!pdf) {
        throw std::runtime_error("Failed to create PDF object");
    }

    // Set PDF properties
    HPDF_SetCompressionMode(pdf, HPDF_COMP_ALL);

    // Load fonts
    defaultFont = HPDF_GetFont(pdf, "Helvetica", nullptr);
    boldFont = HPDF_GetFont(pdf, "Helvetica-Bold", nullptr);
}

PDFGenerator::~PDFGenerator() {
    if (pdf) {
        HPDF_Free(pdf);
    }
}

bool PDFGenerator::generatePDF(const Resume& resume, const std::string& outputPath) {
    try {
        HPDF_Page page = HPDF_AddPage(pdf);
        HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

        float currentY = PAGE_HEIGHT - MARGIN;

        // Draw sections
        drawHeader(resume, page);
        currentY -= 3 * LINE_HEIGHT;
        
        drawEducation(resume, page, currentY);
        currentY -= 2 * LINE_HEIGHT;
        
        drawExperience(resume, page, currentY);
        currentY -= 2 * LINE_HEIGHT;
        
        drawSkills(resume, page, currentY);

        // Save the PDF
        HPDF_SaveToFile(pdf, outputPath.c_str());
        return true;
    } catch (...) {
        return false;
    }
}

void PDFGenerator::drawHeader(const Resume& resume, HPDF_Page page) {
    float centerX = PAGE_WIDTH / 2;
    float y = PAGE_HEIGHT - MARGIN;

    // Name
    HPDF_Page_SetFontAndSize(page, boldFont, 24);
    float nameWidth = getTextWidth(page, resume.getName());
    drawText(page, centerX - nameWidth/2, y, resume.getName());

    // Contact Info
    y -= LINE_HEIGHT * 1.5;
    HPDF_Page_SetFontAndSize(page, defaultFont, 12);
    
    std::string contactInfo = resume.getEmail() + " | " + 
                             resume.getPhone() + " | " + 
                             resume.getLocation();
    
    float contactWidth = getTextWidth(page, contactInfo);
    drawText(page, centerX - contactWidth/2, y, contactInfo);
}

void PDFGenerator::drawEducation(const Resume& resume, HPDF_Page page, float& y) {
    HPDF_Page_SetFontAndSize(page, boldFont, 16);
    drawText(page, MARGIN, y, "Education");
    y -= LINE_HEIGHT * 1.5;

    HPDF_Page_SetFontAndSize(page, defaultFont, 12);
    for (const auto& edu : resume.getEducation()) {
        drawBoldText(page, MARGIN, y, edu.school);
        std::string dateRange = edu.startDate + " - " + edu.endDate;
        float dateWidth = getTextWidth(page, dateRange);
        drawText(page, PAGE_WIDTH - MARGIN - dateWidth, y, dateRange);
        
        y -= LINE_HEIGHT;
        std::string degreeInfo = edu.degree + " in " + edu.field;
        drawText(page, MARGIN + 20, y, degreeInfo);
        if (edu.gpa > 0) {
            std::string gpaStr = "GPA: " + std::to_string(edu.gpa);
            float gpaWidth = getTextWidth(page, gpaStr);
            drawText(page, PAGE_WIDTH - MARGIN - gpaWidth, y, gpaStr);
        }
        y -= LINE_HEIGHT * 1.5;
    }
}

void PDFGenerator::drawExperience(const Resume& resume, HPDF_Page page, float& y) {
    HPDF_Page_SetFontAndSize(page, boldFont, 16);
    drawText(page, MARGIN, y, "Professional Experience");
    y -= LINE_HEIGHT * 1.5;

    HPDF_Page_SetFontAndSize(page, defaultFont, 12);
    for (const auto& exp : resume.getExperience()) {
        drawBoldText(page, MARGIN, y, exp.company);
        std::string dateRange = exp.startDate + " - " + exp.endDate;
        float dateWidth = getTextWidth(page, dateRange);
        drawText(page, PAGE_WIDTH - MARGIN - dateWidth, y, dateRange);
        
        y -= LINE_HEIGHT;
        drawText(page, MARGIN + 20, y, exp.position);
        y -= LINE_HEIGHT;

        for (const auto& resp : exp.responsibilities) {
            drawText(page, MARGIN + 40, y, "• " + resp);
            y -= LINE_HEIGHT;
        }
        y -= LINE_HEIGHT;
    }
}

void PDFGenerator::drawSkills(const Resume& resume, HPDF_Page page, float& y) {
    HPDF_Page_SetFontAndSize(page, boldFont, 16);
    drawText(page, MARGIN, y, "Skills");
    y -= LINE_HEIGHT * 1.5;

    HPDF_Page_SetFontAndSize(page, defaultFont, 12);
    for (const auto& skill : resume.getSkills()) {
        drawBoldText(page, MARGIN, y, skill.category + ":");
        
        std::string skillList;
        for (size_t i = 0; i < skill.items.size(); ++i) {
            skillList += skill.items[i];
            if (i < skill.items.size() - 1) {
                skillList += ", ";
            }
        }
        
        y -= LINE_HEIGHT;
        drawText(page, MARGIN + 20, y, skillList);
        y -= LINE_HEIGHT;
    }
}

void PDFGenerator::drawText(HPDF_Page page, float x, float y, const std::string& text) {
    HPDF_Page_BeginText(page);
    HPDF_Page_MoveTextPos(page, x, y);
    HPDF_Page_ShowText(page, text.c_str());
    HPDF_Page_EndText(page);
}

void PDFGenerator::drawBoldText(HPDF_Page page, float x, float y, const std::string& text) {
    HPDF_Font currentFont = HPDF_Page_GetCurrentFont(page);
    HPDF_REAL currentSize = HPDF_Page_GetCurrentFontSize(page);
    
    HPDF_Page_SetFontAndSize(page, boldFont, currentSize);
    drawText(page, x, y, text);
    
    HPDF_Page_SetFontAndSize(page, currentFont, currentSize);
}

float PDFGenerator::getTextWidth(HPDF_Page page, const std::string& text) {
    HPDF_Font font = HPDF_Page_GetCurrentFont(page);
    HPDF_REAL size = HPDF_Page_GetCurrentFontSize(page);
    return HPDF_Page_TextWidth(page, text.c_str());
} 