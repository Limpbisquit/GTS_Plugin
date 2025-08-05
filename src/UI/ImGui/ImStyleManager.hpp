#pragma once

#include "UI/ImGui/Lib/imgui.h"
#include "Config/Config.hpp"

namespace GTS {

    //Inspired by Community shaders
    class ImStyleManager {

        private:
        SettingsUI& Settings = Config::GetUI();

        static void InitializeDefaultStyle(ImGuiStyle& style);
        void ApplyAccentColor(ImGuiStyle& style) const;
        void SetupStyleImpl() const;

        static inline ImVec4 CalculateContrastColor(const ImVec4& background) {
            const float luminance = 0.2126f * background.x + 
                                    0.7152f * background.y + 
                                    0.0722f * background.z;
            return (luminance > 0.5f) ? ImVec4(0.0f, 0.0f, 0.0f, 1.0f) 
                                      : ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        }

        static inline ImVec4 AdjustAlpha(const ImVec4& color, float alpha) {
            return {color.x, color.y, color.z, alpha};
        }

        public:
        ~ImStyleManager() = default;
        [[nodiscard]] static inline ImStyleManager& GetSingleton() {
            static ImStyleManager instance;
            return instance;
        }

        [[nodiscard]] inline float GetScale() const {
            return Settings.fScale;
        }

        inline void LoadStyle() const {
            SetupStyleImpl();
        }

    };
}