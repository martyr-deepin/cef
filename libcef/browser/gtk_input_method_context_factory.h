//
// Created by xinkai on 1/28/16.
//

#ifndef REMOTE_CEF_GTK2INPUTMETHODCONTEXTFACTORY_H
#define REMOTE_CEF_GTK2INPUTMETHODCONTEXTFACTORY_H

#include "ui/base/ime/linux/linux_input_method_context_factory.h"

class GtkInputMethodContextFactory : public ui::LinuxInputMethodContextFactory {

public:
  GtkInputMethodContextFactory();

//  // Returns the current active factory or NULL.
//  static const GtkInputMethodContextFactory* instance();
//
//  // Sets the dynamically loaded singleton that creates an input method context.
//  // This pointer is not owned, and if this method is called a second time,
//  // the first instance is not deleted.
//  static void SetInstance(const GtkInputMethodContextFactory* instance);
//
  ~GtkInputMethodContextFactory();

  // Returns a native input method context.
  std::unique_ptr<ui::LinuxInputMethodContext> CreateInputMethodContext(
    ui::LinuxInputMethodContextDelegate* delegate,
    bool is_simple) const override;
};

#endif //REMOTE_CEF_GTK2INPUTMETHODCONTEXTFACTORY_H
