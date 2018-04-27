// kX Driver / kX Driver Interface / kX Driver Effects Library
// Copyright (c) Eugene Gavrilov and Max Mikhailov, 2001-2005.
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

#ifndef _KX_REVERBEAX2_EFFECT_H
#define _KX_REVERBEAX2_EFFECT_H

#define REVERBEAX2_PARAMS_COUNT	1	// number of user-visible parameters

class iReverbEax2Plugin : public iKXPlugin
{
public:
	virtual int request_microcode();
	virtual iKXPluginGUI *create_cp(kDialog *parent, kFile *mf);
	virtual const char *get_plugin_description(int id);
	virtual int get_user_interface();
	virtual int get_param_count(void) {return REVERBEAX2_PARAMS_COUNT;}
	virtual int describe_param(int, kx_fxparam_descr*);
	virtual int set_defaults();
    virtual int set_param(int ndx, kxparam_t value);
	virtual int get_param(int ndx, kxparam_t *value);
	virtual int set_all_params(kxparam_t* values);
	virtual const kxparam_t *get_plugin_presets();
	
	kxparam_t _params[REVERBEAX2_PARAMS_COUNT];
};

class iReverbEax2PluginDlg : public CKXPluginGUI
{
public:
	iReverbEax2Plugin *plugin;

    	// constructor:
	iReverbEax2PluginDlg(iReverbEax2Plugin *plg, kDialog *parent_, kFile *mf_) : CKXPluginGUI(parent_,mf_) {plugin = plg; };

	virtual void init();
	virtual iKXPlugin *get_plugin() { return plugin; };	
};


declare_effect_source(ReverbEax2);

#endif
