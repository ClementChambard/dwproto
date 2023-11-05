#include "./editor.hpp"
#include "./RoomCollider.hpp"
#include <Engine.hpp>
#include <NSEngine.h>
#include <imgui.h>
#include <imguiW.hpp>
#include <vector>

class ImGuiEventProcessor : public NSEngine::IEventProcessor {
public:
  ~ImGuiEventProcessor() override {}
  void ProcessEvent(SDL_Event *e, bool &noKeyboard, bool &noMouse) override {
    ImGui_ImplSDL2_ProcessEvent(e);

    ImGuiIO &io = ImGui::GetIO();
    noKeyboard = io.WantCaptureKeyboard;
    noMouse = io.WantCaptureMouse;
  }
};

static ImGuiEventProcessor *igep = nullptr;

static RoomCollider rc;
void Editor::init() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplOpenGL3_Init("#version 130");
  ImGui_ImplSDL2_InitForOpenGL(
      NSEngine::getInstance()->window().getSdlWindow(),
      NSEngine::getInstance()->window().getSdlGlContext());
  ImGuiIO &io = ImGui::GetIO();
  io.IniFilename = "";
  ImGui::StyleColorsDark();
  igep = new ImGuiEventProcessor();
  NSEngine::engineData::eventProcessors.push_back(igep);
  NSEngine::InputManager::SetAsEventProcessor();
  rc.testEnv();
}

Editor::~Editor() {
  delete igep;
  igep = nullptr;
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
}

void Editor::on_tick() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();
  ImGui::Begin("Browser");
  if (ImGui::TreeNode("Planes")) {
    int i = 0;
    ImGui::PushID("Planes");
    for (auto &p : rc.m_planes) {
      ImGui::PushID(i);
      if (ImGui::TreeNode("plane")) {
        ImGui::InputFloat2("pos_low", &p.coord_low[0]);
        ImGui::InputFloat2("pos_high", &p.coord_high[0]);
        ImGui::InputFloat("elevation_low", &p.elevation_at_low_coord);
        ImGui::InputFloat("elevation_high", &p.elevation_at_high_coord);
        ImGui::InputInt("slope type", reinterpret_cast<int *>(&p.slope_type));
        ImGui::TreePop();
      }
      i++;
      ImGui::PopID();
    }
    ImGui::PopID();
    ImGui::TreePop();
  }
  if (ImGui::TreeNode("Walls")) {
    int i = 0;
    ImGui::PushID("Planes");
    for (auto &w : rc.m_walls) {
      ImGui::PushID(i);
      if (ImGui::TreeNode("wall")) {
        ImGui::InputFloat2("pos_1", &w.point_xz_1[0]);
        ImGui::InputFloat2("pos_2", &w.point_xz_2[0]);
        ImGui::InputFloat("elevation_low", &w.elevation_low);
        ImGui::InputFloat("elevation_high", &w.elevation_high);
        ImGui::TreePop();
      }
      i++;
      ImGui::PopID();
    }
    ImGui::PopID();
    ImGui::TreePop();
  }
  ImGui::End();
}
void Editor::on_draw() {
  // draw planes and walls here
  rc.debug_draw();
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
