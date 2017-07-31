//
// Created by xinkai on 1/28/16.
//

#include "libcef/browser/gtk_input_method_context_factory.h"

#include <gtk/gtk.h>
#include "chrome/browser/ui/libgtkui/gtk_event_loop.h"
#include "chrome/browser/ui/libgtkui/gtk_ui.h"
#include "chrome/browser/ui/libgtkui/libgtkui_export.h"
#include "chrome/browser/ui/libgtkui/x11_input_method_context_impl_gtk.h"
#include "ui/base/ime/input_method_auralinux.h" // LinuxInputMethodContextDelegate

#include "base/command_line.h"


void CommonInitFromCommandLine(const base::CommandLine& command_line,
                               void (*init_func)(gint*, gchar***)) {
  const std::vector<std::string>& args = command_line.argv();
  int argc = args.size();
  std::unique_ptr<char *[]> argv(new char *[argc + 1]);
  for (size_t i = 0; i < args.size(); ++i) {
    // TODO(piman@google.com): can gtk_init modify argv? Just being safe
    // here.
    argv[i] = strdup(args[i].c_str());
  }
  argv[argc] = NULL;
  char **argv_pointer = argv.get();

  {
    // http://crbug.com/423873
    ANNOTATE_SCOPED_MEMORY_LEAK;
    init_func(&argc, &argv_pointer);
  }
  for (size_t i = 0; i < args.size(); ++i) {
    free(argv[i]);
  }
}

GtkInputMethodContextFactory::GtkInputMethodContextFactory() {
  CommonInitFromCommandLine(*base::CommandLine::ForCurrentProcess(), gtk_init);
  libgtkui::Gtk2EventLoop::GetInstance();
}

GtkInputMethodContextFactory::~GtkInputMethodContextFactory() {
  // TODO: need to delete libgtkui::Gtk2EventLoop::GetInstance()
}

std::unique_ptr<ui::LinuxInputMethodContext>
GtkInputMethodContextFactory::CreateInputMethodContext(
  ui::LinuxInputMethodContextDelegate* delegate,
  bool is_simple) const {
  return std::unique_ptr<ui::LinuxInputMethodContext>(
    new libgtkui::X11InputMethodContextImplGtk2(delegate, is_simple));
}
