#include "MainFrame.h"
#include "../core/RLE.h"

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, wxString::FromUTF8("Compresión RLE"), wxDefaultPosition, wxSize(600, 500))
{
    wxPanel *panel = new wxPanel(this);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    inputText = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    wxButton *button = new wxButton(panel, wxID_ANY, wxString::FromUTF8("Codificar/Decodificar"));
    encodedText = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
    decodedText = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
    statsText = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);

    sizer->Add(new wxStaticText(panel, wxID_ANY, wxString::FromUTF8("Entrada:")), 0, wxALL, 5);
    sizer->Add(inputText, 1, wxEXPAND | wxALL, 5);
    sizer->Add(button, 0, wxEXPAND | wxALL, 5);
    sizer->Add(new wxStaticText(panel, wxID_ANY, wxString::FromUTF8("Codificado:")), 0, wxALL, 5);
    sizer->Add(encodedText, 1, wxEXPAND | wxALL, 5);
    sizer->Add(new wxStaticText(panel, wxID_ANY, wxString::FromUTF8("Decodificado:")), 0, wxALL, 5);
    sizer->Add(decodedText, 1, wxEXPAND | wxALL, 5);
    sizer->Add(new wxStaticText(panel, wxID_ANY, wxString::FromUTF8("Estadísticas:")), 0, wxALL, 5);
    sizer->Add(statsText, 1, wxEXPAND | wxALL, 5);

    panel->SetSizer(sizer);

    button->Bind(wxEVT_BUTTON, &MainFrame::OnProcess, this);
}

void MainFrame::OnProcess(wxCommandEvent &event)
{
    // Get input and convert from wxString to UTF-8 std::string
    wxString inputWx = inputText->GetValue();
    std::string input = std::string(inputWx.utf8_str());

    std::string encoded = RLE::encode(input);
    std::string decoded = RLE::decode(encoded);

    // Convert UTF-8 std::string back to wxString for display
    encodedText->SetValue(wxString::FromUTF8(encoded));
    decodedText->SetValue(wxString::FromUTF8(decoded));

    size_t originalBytes = input.size();
    size_t encodedBytes = encoded.size();

    wxString result;
    if (encodedBytes < originalBytes)
        result = wxString::FromUTF8("Compresión positiva");
    else if (encodedBytes > originalBytes)
        result = wxString::FromUTF8("Compresión negativa");
    else
        result = wxString::FromUTF8("Sin compresión");

    wxString stats = wxString::Format(
        wxString::FromUTF8("Original: %lu bytes\nCodificado: %lu bytes\nResultado: %s"),
        (unsigned long)originalBytes,
        (unsigned long)encodedBytes,
        result.c_str());

    statsText->SetValue(stats);
}