// kX Mixer
// Copyright (c) Eugene Gavrilov, 2001-2005.
// All rights reserved

/*
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */


#if !defined(AFX_MYDIALOG_H__B294EF63_CE1F_4020_B1F8_573626C3E571__INCLUDED_)
#define AFX_MYDIALOG_H__B294EF63_CE1F_4020_B1F8_573626C3E571__INCLUDED_

#pragma once

class CSpeakerDialog : public CKXDialog
{
public:
	CSpeakerDialog(iKX *dev) { ikx_t=dev; };
        const char *get_class_name() { return "kXSpeaker"; };

	kButton b_8ps[8+1];

	kButton b_ok;
	kButton b_test;

	kStatic label;

	int select_device(int dev_=-1);

	void test_channel(char *id,dword routing);
	void test_channel(int chn);
	int show_channel(int chn); // returns '0' if channel is actually present

#define SHOW_N		0
#define SHOW_NW		1
#define SHOW_W		2
#define SHOW_SW		3
#define SHOW_S		4
#define SHOW_SE		5
#define SHOW_E		6
#define SHOW_NE		7
#define SHOW_SUBWOOFER  8
#define TOTAL		9

	virtual void init();

	int is_a2;

        int on_command(int wparam,int lparam);
};

#endif // !defined(AFX_MYDIALOG_H__B294EF63_CE1F_4020_B1F8_573626C3E571__INCLUDED_)
