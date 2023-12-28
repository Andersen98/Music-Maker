#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include <ftxui/dom/elements.hpp>  // for separator, operator|, Element, size, xflex, text, WIDTH, hbox,  border, GREATER_THAN
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include <ftxui/component/component.hpp> //for Renderer, Buttoon, Horizontal
#include "ftxui/component/component_options.hpp"   // for ButtonOption
#include "ftxui/screen/color.hpp"  // for Color,  Color::Red
#include <memory>  // for shared_ptr, __shared_ptr_access
#include <string>  // for operator+, to_string
 
using namespace ftxui;
int main(void) {
  int value = 50;
  bool is_playing = false;

  auto button = Button("play/pause", [&] { is_playing = !is_playing; },  ButtonOption::Animated(Color::Red));
  auto slider = Slider("tune:", &value, 0, 100, 1);
  
  // Tree of components that defines how to navigate using keyboard
  auto layout = Container::Horizontal({
    button,
    slider,
  });

  //Modify the way to render on screen
  auto component = Renderer(layout, [&] {
          return hbox({
                  button->Render(),
                  separator(),
                  slider->Render() | flex | size(WIDTH, GREATER_THAN, 40),
                  separator(),
                  vbox({
                    text("frequency = " + std::to_string(value)),
                    separator(),
                    text("is playing: " + std::to_string(is_playing)),
                  }) | border }) | flex | border;
          });

  auto screen = ScreenInteractive::FitComponent();
  screen.Loop(component); 
  return EXIT_SUCCESS;
}
