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
 * @file frmMain.h - Header file for the frmMain class.
**/

#ifndef FRMMAIN_H_INCLUDED
#define FRMMAIN_H_INCLUDED

#include <wx/wx.h>
#include <wx/aboutdlg.h>
#include <wx/colour.h>
#include <wx/ffile.h>
#include <wx/filedlg.h>
#include <wx/menu.h>
#include <wx/string.h>
#include "Clipboard.h"
#include "MD5.h"

class frmMain : public wxFrame
{
public:

    frmMain(void);

    /** Menu Bar **/

    wxMenuBar *menuBar;

    wxMenu *mnuFile;
    //
    wxMenuItem *miOpen;
    // Separator
    wxMenuItem *miQuit;

    wxMenu *mnuHelp;
    //
    wxMenuItem *miAbout;

    /** Main Window **/

    wxPanel *pnlMargin;
    wxBoxSizer *vboxMargin;

    wxPanel *pnlMain;
    wxBoxSizer *vboxMain;

    wxBoxSizer *hboxFileInput;
    wxStaticText *lblFile;
    wxTextCtrl *txtFile;
    wxButton *btnBrowse;

    wxBoxSizer *hboxMD5Output;
    wxStaticText *lblMD5;
    wxTextCtrl *txtMD5;
    wxButton *btnCopyMD5;

    // :TODO: 2012-05-27 gbchaosmaster - Implement SHA-1.

//  wxBoxSizer *hboxSHA1Output;
//  wxStaticText *lblSHA1;
//  wxTextCtrl *txtSHA1;
//  wxButton *btnCopySHA1;

    wxBoxSizer *hboxCompare;
    wxStaticText *lblCompare;
    wxTextCtrl *txtCompare;
    wxButton *btnCompare;

    /** Events **/

    void selectFile(wxCommandEvent &event);
    void compare(wxCommandEvent &event);
    void copyMD5(wxCommandEvent &event);
//  void copySHA1(wxCommandEvent &event);
    void showAbout(wxCommandEvent &event);
    void quit(wxCommandEvent &event);

    /** Functions **/

    void copyChecksum(wxString str);

private:

    /** Identifiers **/

    static const long ID_COMPARE;
    static const long ID_COPY_MD5;
//  static const long ID_COPY_SHA1;
    static const long ID_BROWSE;
    static const long ID_OPEN;
};

#endif // FRMMAIN_H_INCLUDED

