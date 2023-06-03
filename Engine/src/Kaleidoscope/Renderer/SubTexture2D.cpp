#include "kldpch.h"
#include "Kaleidoscope/Renderer/SubTexture2D.h"

namespace Kaleidoscope
{
    SubTexture2D::SubTexture2D(const Ref<Texture2D> &texture, const glm::vec2 &min, const glm::vec2 &max)
        : m_Texture(texture)
    {
        m_TexCoords[0] = {min.x, min.y}; // 左下
        m_TexCoords[1] = {max.x, min.y}; // 右下
        m_TexCoords[2] = {max.x, max.y}; // 右上
        m_TexCoords[3] = {min.x, max.y}; // 左上
    }

    Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D> &texture, const glm::vec2 &coords, const glm::vec2 &cellSize, const glm::vec2 &spriteSize)
    {
        // coords 表示sprite sheet上，从左边往右数第x个、从下往上数第y个texture
        // spriteSize 表示sprite sheet上每个texture的大小

        // 将sprite sheet中的某一个区域重现映射到[0,1]区间内
        glm::vec2 min = {
            (coords.x * cellSize.x) / texture->GetWidth(),
            (coords.y * cellSize.y) / texture->GetHeight()};

        glm::vec2 max = {
            ((coords.x + spriteSize.x) * cellSize.x) / texture->GetWidth(),
            ((coords.y + spriteSize.y) * cellSize.y) / texture->GetHeight()};

        return CreateRef<SubTexture2D>(texture, min, max);
    }

} // namespace Kaleidoscope
