// -*- mode: C++; indent-tabs-mode: nil; c-basic-offset: 2; -*-
// epist.hh for Epistrophy - a key handler for NETWM/EWMH window managers.
// Copyright (c) 2002 - 2002 Ben Jansens <ben at orodu.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef   __epist_hh
#define   __epist_hh

extern "C" {
#include <X11/Xlib.h>
}

#include <string>
#include <map>

#include "actions.hh"
#include "window.hh"
#include "keytree.hh"
#include "config.hh"

#include "../../src/basedisplay.hh"

class XAtom;
class screen;

class epist : public BaseDisplay {
private:
  std::string _rc_file;
  XAtom *_xatom;
  char **_argv;
  keytree *_ktree;
  Config *_config;

  typedef std::vector<screen *> ScreenList;
  ScreenList _screens;

  typedef std::map<Window, XWindow*> WindowLookup;
  typedef WindowLookup::value_type WindowLookupPair;
  WindowLookup    _windows;
  
  WindowList _clients;
  WindowList::iterator _active;

  ActionList _actions;
  
  virtual void process_event(XEvent *e);
  virtual bool handleSignal(int sig);

  void activateGrabs();

public:
  epist(char **argv, char *display_name, char *rc_file);
  virtual ~epist();

  inline XAtom *xatom() { return _xatom; }

  void addWindow(XWindow *window);
  void removeWindow(XWindow *window);
  XWindow *findWindow(Window window) const;

  void cycleScreen(int current, bool forward) const;

  void getLockModifiers(int &numlockMask, int &scrolllockMask) const {
    numlockMask = NumLockMask;
    scrolllockMask = ScrollLockMask;
  }
  
  const ActionList &actions(void) { return _actions; }
  keytree &getKeyTree(void) { return *_ktree; }
  inline const Config *getConfig(void) { return _config; }

  WindowList& clientsList() { return _clients; }
  WindowList::iterator& activeWindow() { return _active; }
};

#endif // __epist_hh
