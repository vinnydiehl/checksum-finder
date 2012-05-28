/**
 * A program for verifying file integrity.
 * Copyright (C) 2012 Vinny Diehl
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
**/

/**
 * @file frmMain.cpp - The main wxFrame for the application.
**/

#include "frmMain.h"

const wxString TITLE = _T("Checksum Finder");
const int MIN_WIDTH = 550;
const char MARGIN = 5;
const char SEPARATOR = 2;

/** Initialize Identifiers **/

const long frmMain::ID_COMPARE = wxNewId();
const long frmMain::ID_COPY_MD5 = wxNewId();
//const long frmMain::ID_COPY_SHA1 = wxNewId();
const long frmMain::ID_OPEN = wxNewId();
const long frmMain::ID_BROWSE = wxNewId();

frmMain::frmMain(void) : wxFrame(NULL, wxID_ANY, TITLE)
{
    /** Menu Bar **/

    menuBar = new wxMenuBar;

    // File
    mnuFile = new wxMenu;

    miOpen = new wxMenuItem(mnuFile, ID_OPEN, _T("&Open\tCtrl+O"));
    miQuit = new wxMenuItem(mnuFile, wxID_EXIT, _T("&Quit\tCtrl+W"));

    mnuFile->Append(miOpen);
    mnuFile->AppendSeparator();
    mnuFile->Append(miQuit);

    // Help
    mnuHelp = new wxMenu;

    miAbout = new wxMenuItem(mnuHelp, wxID_ABOUT, _T("&About\tF1"));

    mnuHelp->Append(miAbout);

    // Assemble the menu bar
    menuBar->Append(mnuFile, _T("&File"));
    menuBar->Append(mnuHelp, _T("&Help"));
    SetMenuBar(menuBar);

    // Connect menu bar events
    Connect(ID_OPEN, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(frmMain::selectFile));
    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(frmMain::quit));
    Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(frmMain::showAbout));

    /** Main Window **/

    pnlMargin = new wxPanel(this, wxID_ANY);
    vboxMargin = new wxBoxSizer(wxVERTICAL);

    pnlMain = new wxPanel(pnlMargin, wxID_ANY);
    vboxMain = new wxBoxSizer(wxVERTICAL);

    hboxFileInput = new wxBoxSizer(wxHORIZONTAL);

    lblFile = new wxStaticText(pnlMain, wxID_ANY, _T("File:"));
    txtFile = new wxTextCtrl(pnlMain, wxID_ANY);
    btnBrowse = new wxButton(pnlMain, ID_BROWSE, _T("&Browse..."));

    hboxFileInput->Add(lblFile, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    hboxFileInput->Add(txtFile, 1, wxALIGN_CENTER_VERTICAL);
    hboxFileInput->Add(btnBrowse, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);

    vboxMain->Add(hboxFileInput, 0, wxEXPAND);
    vboxMain->Add(-1, SEPARATOR);

    // End hboxFileInput

    hboxMD5Output = new wxBoxSizer(wxHORIZONTAL);

    lblMD5 = new wxStaticText(pnlMain, wxID_ANY, _T("MD5 Checksum:"));
    txtMD5 = new wxTextCtrl(pnlMain, wxID_ANY, wxEmptyString,
                            wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    btnCopyMD5 = new wxButton(pnlMain, ID_COPY_MD5, _T("Copy &MD5"));

    txtMD5->SetBackgroundColour(*wxLIGHT_GREY);

    hboxMD5Output->Add(lblMD5, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    hboxMD5Output->Add(txtMD5, 1, wxALIGN_CENTER_VERTICAL);
    hboxMD5Output->Add(btnCopyMD5, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);

    vboxMain->Add(hboxMD5Output, 0, wxEXPAND);
    vboxMain->Add(-1, SEPARATOR);

    // End hboxMD5Output

    // :TODO: 2012-05-27 gbchaosmaster - Implement SHA-1.

//  hboxSHA1Output = new wxBoxSizer(wxHORIZONTAL);

//  lblSHA1 = new wxStaticText(pnlMain, wxID_ANY, _T("SHA1 Checksum:"));
//  txtSHA1 = new wxTextCtrl(pnlMain, wxID_ANY, wxEmptyString,
//                           wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
//  btnCopySHA1 = new wxButton(pnlMain, ID_COPY_SHA1, _T("Copy &SHA1"));

//  txtSHA1->SetBackgroundColour(*wxLIGHT_GREY);

//  hboxSHA1Output->Add(lblSHA1, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
//  hboxSHA1Output->Add(txtSHA1, 1, wxALIGN_CENTER_VERTICAL);
//  hboxSHA1Output->Add(btnCopySHA1, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);

//  vboxMain->Add(hboxSHA1Output, 0, wxEXPAND);
//  vboxMain->Add(-1, SEPARATOR);

    // End hboxSHA1Output

    hboxCompare = new wxBoxSizer(wxHORIZONTAL);

    lblCompare = new wxStaticText(pnlMain, wxID_ANY, _T("Compare Checksums:"));
    txtCompare = new wxTextCtrl(pnlMain, wxID_ANY);
    btnCompare = new wxButton(pnlMain, ID_COMPARE, _T("&Compare"));

    hboxCompare->Add(lblCompare, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    hboxCompare->Add(txtCompare, 1, wxALIGN_CENTER_VERTICAL);
    hboxCompare->Add(btnCompare, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);

    vboxMain->Add(hboxCompare, 0, wxEXPAND);
    // Bottom hbox, no separator

    // End hboxCompare

    pnlMain->SetSizer(vboxMain);

    vboxMargin->Add(pnlMain, 1, wxEXPAND | wxALL, MARGIN);
    vboxMargin->SetSizeHints(this);
    pnlMargin->SetSizer(vboxMargin);

    // :TODO: 2012-05-27 gbchaosmaster - Have txtFile accept Enter.
    // It will process the file, but we'll need a check to make sure that it
    // exists before we go on.

    // Connect main window events
    Connect(ID_BROWSE, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(frmMain::selectFile));
    Connect(ID_COPY_MD5, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(frmMain::copyMD5));
//  Connect(ID_COPY_SHA1, wxEVT_COMMAND_BUTTON_CLICKED,
//          wxCommandEventHandler(frmMain::copySHA1));
    Connect(ID_COMPARE, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(frmMain::compare));

    /** Configure Form **/

    // Set the minimum/startup width, height will be figured out by the sizers
    SetMinSize(wxSize(MIN_WIDTH, -1));
    // Don't let the user change the height
    SetMaxSize(wxSize(wxDefaultCoord, GetSize().y));
    // Center the window on screen on startup
    Center();
}

void frmMain::selectFile(wxCommandEvent &WXUNUSED(event))
{
    // Let the user select a file from the dialog
    wxFileDialog dlgOpenFile(this, _T("Select a File"), wxGetHomeDir(),
                             wxEmptyString, _T("All Files|*.*"),
                             wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    // If they pressed cancel, stop
    if (dlgOpenFile.ShowModal() == wxID_CANCEL) return;

    // Set the selected file path to the text box
    txtFile->SetValue(dlgOpenFile.GetPath());

    // Read the entire file into a wxString
    wxString contents;
    wxFFile file(dlgOpenFile.GetPath());
    file.ReadAll(&contents);
    file.Close();

    txtMD5->SetValue(encryptMD5(contents));
}

void frmMain::compare(wxCommandEvent &WXUNUSED(event))
{
    // Trim whitespace from ends of the pasted hash
    txtCompare->SetValue(txtCompare->GetValue().Trim()); // End
    txtCompare->SetValue(txtCompare->GetValue().Trim(false)); // Beginning

    // Check if it's a good/bad match and tell them the result
    if (txtCompare->GetValue() == txtMD5->GetValue())
        wxMessageBox(_T("The MD5 hash matches."), _T("Good Match"));
    else wxMessageBox(_T("The MD5 hash does not match."), _T("Bad Match"));
}

void frmMain::copyChecksum(wxString str)
{
    if (!str.IsEmpty())
    {
        Clipboard::SetClipboard(str);

        if (Clipboard::GetClipboard() == str)
            wxMessageBox(_T("Checksum copied successfully."), _T("Success"));
    }
}
void frmMain::copyMD5(wxCommandEvent &WXUNUSED(event))
{
    copyChecksum(txtMD5->GetValue());
}
//void frmMain::copySHA1(wxCommandEvent &WXUNUSED(event))
//{
//  copyChecksum(txtSHA1->GetValue());
//}

/** Miscellaneous Functions **/

void frmMain::showAbout(wxCommandEvent &WXUNUSED(event))
{
    wxAboutDialogInfo info;
    info.SetName(_T("Checksum Finder"));
    info.SetVersion(_T("1.0a1"));
    info.SetDescription(_T("Finds the MD5/SHA-1 checksums of a file."));
    info.SetCopyright(_T("Copyright (c) 2012 Vinny Diehl"));

    wxAboutBox(info);
}

void frmMain::quit(wxCommandEvent &WXUNUSED(event))
{
    Close();
}

