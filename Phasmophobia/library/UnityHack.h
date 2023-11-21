// ReSharper disable StringLiteralTypo
// ReSharper disable CppInconsistentNaming
// ReSharper disable CppUninitializedNonStaticDataMember
// ReSharper disable IdentifierTypo
// ReSharper disable CppDeclarationHidesLocal
#pragma once
#include <Windows.h>
#include <string>
#include <unordered_map>
#include <fstream>
#include <list>
#include <format>
#include "Console.hpp"

// 请使用OneApi Base包内Intel C++ 编译器打开MKL选项后编
// #include <mkl.h>

#ifdef _WIN64
#define CALLING_CONVENTION __fastcall
#elif _WIN32
#define CALLING_CONVENTION __cdecl
#endif

namespace unity {
    class CSharper {
    public:
        struct Vector3 {
            float x, y, z;

            Vector3() { x = y = z = 0.f; }

            Vector3(const float f1, const float f2, const float f3) {
                x = f1;
                y = f2;
                z = f3;
            }

            auto Length() const -> float { return x * x + y * y + z * z; }

            auto Dot(const Vector3 b) const -> float { return x * b.x + y * b.y + z * b.z; }

            auto Normalize() const -> Vector3 {
                const float len = Length();
                if (len > 0)
                    return Vector3(x / len, y / len, z / len);
                return Vector3(x, y, z);
            }

            auto ToVectors(Vector3* m_pForward, Vector3* m_pRight, Vector3* m_pUp) const -> void {
                constexpr float m_fDeg2Rad = static_cast<float>(3.1415926) / 180.F;

                const float m_fSinX = sinf(x * m_fDeg2Rad);
                const float m_fCosX = cosf(x * m_fDeg2Rad);

                const float m_fSinY = sinf(y * m_fDeg2Rad);
                const float m_fCosY = cosf(y * m_fDeg2Rad);

                const float m_fSinZ = sinf(z * m_fDeg2Rad);
                const float m_fCosZ = cosf(z * m_fDeg2Rad);

                if (m_pForward) {
                    m_pForward->x = m_fCosX * m_fCosY;
                    m_pForward->y = -m_fSinX;
                    m_pForward->z = m_fCosX * m_fSinY;
                }

                if (m_pRight) {
                    m_pRight->x = -1.f * m_fSinZ * m_fSinX * m_fCosY + -1.f * m_fCosZ * -m_fSinY;
                    m_pRight->y = -1.f * m_fSinZ * m_fCosX;
                    m_pRight->z = -1.f * m_fSinZ * m_fSinX * m_fSinY + -1.f * m_fCosZ * m_fCosY;
                }

                if (m_pUp) {
                    m_pUp->x = m_fCosZ * m_fSinX * m_fCosY + -m_fSinZ * -m_fSinY;
                    m_pUp->y = m_fCosZ * m_fCosX;
                    m_pUp->z = m_fCosZ * m_fSinX * m_fSinY + -m_fSinZ * m_fCosY;
                }
            }

            auto Distance(const Vector3& event) const -> float {
                const float dx = this->x - event.x;
                const float dy = this->y - event.y;
                const float dz = this->z - event.z;
                return std::sqrt(dx * dx + dy * dy + dz * dz);
            }

            /*
            auto Distance(const std::vector<Vector3>& events) const -> std::vector<float> {
                const size_t     numEvents = events.size();
                constexpr int numDimensions = 3;
                const int     numElements = numEvents * numDimensions;

                // 将Vector3对象转换为一维数组
                std::vector<float> coordinates(numElements);
                for (int i = 0; i < numEvents; i++) {
                    coordinates[i * numDimensions + 0] = events[i].x;
                    coordinates[i * numDimensions + 1] = events[i].y;
                    coordinates[i * numDimensions + 2] = events[i].z;
                }

                // 计算距离平方
                std::vector<float> distances(numEvents);
                cblas_sgemv(CblasRowMajor,
                    CblasNoTrans,
                    numEvents,
                    numDimensions,
                    -2.0f,
                    coordinates.data(),
                    numDimensions,
                    &this->x,
                    1,
                    0.0f,
                    distances.data(),
                    1);
                for (auto& distance : distances)
                    distance = std::sqrt(distance);

                return distances;
            }
            */
        };

        struct Vector2 {
            float x, y;

            Vector2() { x = y = 0.f; }

            Vector2(const float f1, const float f2) {
                x = f1;
                y = f2;
            }

            auto Distance(const Vector2& event) const -> float {
                const float dx = this->x - event.x;
                const float dy = this->y - event.y;
                return std::sqrt(dx * dx + dy * dy);
            }

            /*
            auto Distance(const std::vector<Vector2>& events) const -> std::vector<float> {
                const size_t     numEvents = events.size();
                constexpr int numDimensions = 2;
                const int     numElements = numEvents * numDimensions;

                // 将Vector2对象转换为一维数组
                std::vector<float> coordinates(numElements);
                for (int i = 0; i < numEvents; i++) {
                    coordinates[i * numDimensions + 0] = events[i].x;
                    coordinates[i * numDimensions + 1] = events[i].y;
                }

                // 计算距离平方
                std::vector<float> distances(numEvents);
                cblas_sgemv(CblasRowMajor,
                    CblasNoTrans,
                    numEvents,
                    numDimensions,
                    -2.0f,
                    coordinates.data(),
                    numDimensions,
                    &this->x,
                    1,
                    0.0f,
                    distances.data(),
                    1);
                for (auto& distance : distances)
                    distance = std::sqrt(distance);

                return distances;
            }
            */
        };

        struct Vector4 {
            float x, y, z, w;

            Vector4() { x = y = z = w = 0.F; }

            Vector4(const float f1, const float f2, const float f3, const float f4) {
                x = f1;
                y = f2;
                z = f3;
                w = f4;
            }
        };

        struct Quaternion {
            float x, y, z, w;

            Quaternion() { x = y = z = w = 0.F; }

            Quaternion(const float f1, const float f2, const float f3, const float f4) {
                x = f1;
                y = f2;
                z = f3;
                w = f4;
            }

            auto Euler(float m_fX, float m_fY, float m_fZ) -> Quaternion {
                constexpr float m_fDeg2Rad = static_cast<float>(3.1415926) / 180.F;

                m_fX = m_fX * m_fDeg2Rad * 0.5F;
                m_fY = m_fY * m_fDeg2Rad * 0.5F;
                m_fZ = m_fZ * m_fDeg2Rad * 0.5F;

                const float m_fSinX = sinf(m_fX);
                const float m_fCosX = cosf(m_fX);

                const float m_fSinY = sinf(m_fY);
                const float m_fCosY = cosf(m_fY);

                const float m_fSinZ = sinf(m_fZ);
                const float m_fCosZ = cosf(m_fZ);

                x = m_fCosY * m_fSinX * m_fCosZ + m_fSinY * m_fCosX * m_fSinZ;
                y = m_fSinY * m_fCosX * m_fCosZ - m_fCosY * m_fSinX * m_fSinZ;
                z = m_fCosY * m_fCosX * m_fSinZ - m_fSinY * m_fSinX * m_fCosZ;
                w = m_fCosY * m_fCosX * m_fCosZ + m_fSinY * m_fSinX * m_fSinZ;

                return *this;
            }

            auto Euler(const Vector3 m_vRot) -> Quaternion { return Euler(m_vRot.x, m_vRot.y, m_vRot.z); }

            auto ToEuler() const -> Vector3 {
                Vector3 m_vEuler;

                const float m_fDist = (x * x) + (y * y) + (z * z) + (w * w);

                const float m_fTest = x * w - y * z;
                if (m_fTest > 0.4995F * m_fDist) {
                    m_vEuler.x = static_cast<float>(3.1415926) * 0.5F;
                    m_vEuler.y = 2.F * atan2f(y, x);
                    m_vEuler.z = 0.F;
                }
                else if (m_fTest < -0.4995F * m_fDist) {
                    m_vEuler.x = static_cast<float>(3.1415926) * -0.5F;
                    m_vEuler.y = -2.F * atan2f(y, x);
                    m_vEuler.z = 0.F;
                }
                else {
                    m_vEuler.x = asinf(2.F * (w * x - y * z));
                    m_vEuler.y = atan2f(2.F * w * y + 2.F * z * x, 1.F - 2.F * (x * x + y * y));
                    m_vEuler.z = atan2f(2.F * w * z + 2.F * x * y, 1.F - 2.F * (z * z + x * x));
                }

                constexpr float m_fRad2Deg = 180.F / static_cast<float>(3.1415926);
                m_vEuler.x *= m_fRad2Deg;
                m_vEuler.y *= m_fRad2Deg;
                m_vEuler.z *= m_fRad2Deg;

                return m_vEuler;
            }
        };

        struct Bounds {
            Vector3 m_vCenter;
            Vector3 m_vExtents;
        };

        struct Plane {
            Vector3 m_vNormal;
            float   fDistance;
        };

        struct Ray {
            Vector3 m_vOrigin;
            Vector3 m_vDirection;
        };

        struct Rect {
            float fX, fY;
            float fWidth, fHeight;

            Rect() { fX = fY = fWidth = fHeight = 0.f; }

            Rect(const float f1, const float f2, const float f3, const float f4) {
                fX = f1;
                fY = f2;
                fWidth = f3;
                fHeight = f4;
            }
        };

        struct Color {
            float r, g, b, a;

            Color() { r = g = b = a = 0.f; }

            Color(const float fRed = 0.f, const float fGreen = 0.f, const float fBlue = 0.f, const float fAlpha = 1.f) {
                r = fRed;
                g = fGreen;
                b = fBlue;
                a = fAlpha;
            }
        };

        struct Matrix4x4 {
            float m[4][4] = { 0 };

            Matrix4x4() { }

            auto operator[](const int i) -> float* { return m[i]; }
        };

        struct Object {
        protected:
            union {
                struct Class* klass{ nullptr };
                struct VTable* vtable;
            };

            struct MonitorData* monitor{ nullptr };

        public:
            auto GetClass() const -> Class* { return this->klass; }
        };

        struct String : Object {
        protected:
            int32_t m_stringLength{ 0 };
            wchar_t m_firstChar{ 0 };

        public:
            auto ToString() const -> std::string {
                std::string sRet(static_cast<size_t>(m_stringLength) * 3 + 1, '\0');
                WideCharToMultiByte(CP_UTF8,
                    0,
                    &m_firstChar,
                    m_stringLength,
                    &sRet[0],
                    static_cast<int>(sRet.size()),
                    nullptr,
                    nullptr);
                return sRet;
            }
        };

        template<typename T>
        struct Array : Object {
        protected:
            struct {
                size_t length;
                size_t lower_bound;
            }*bounds{ nullptr };

            size_t max_length{ 0 };
            T* vector{ nullptr };

        public:
            auto Size() const -> size_t { return this->max_length; }

            auto Fill(T& v) -> void {
                for (size_t i = 0; i < this->max_length; i++)
                    this->vector[i] = v;
            }

            auto operator[](size_t i) -> T& { return this->vector[i]; }
        };

        template<typename T>
        class List {
        public:
            size_t GetCount() {
                return reinterpret_cast<size_t(*)(void*)>(methodAddress_["List`1.get_Count"])(this);
            }

            void Add(T& t) {
                return reinterpret_cast<size_t(*)(void*)>(methodAddress_["List`1.Add"])(this);
            }

            T& GetItem(size_t index) {
                return reinterpret_cast<T&(*)(void*, size_t)>(methodAddress_["List`1.get_Item"])(this, index);
            }

            void SetItem(size_t index, T& t) {
                return reinterpret_cast<void(*)(void*, size_t, T&)>(methodAddress_["List`1.set_Item"])(this, index, t);
            }

            bool Remove(T& t) {
                return reinterpret_cast<bool(*)(void*, T&)>(methodAddress_["List`1.Remove"])(this);
            }
        };

        struct IL2cpp {
            struct Object {
            public:
                static void Destroy(void* obj) {
                    return reinterpret_cast<void(*)(void*)>(methodAddress_["Object.Destroy"])(obj);
                }

                static void DestroyImmediate(void* obj) {
                    return reinterpret_cast<void(*)(void*)>(methodAddress_["Object.DestroyImmediate"])(obj);
                }
            };

            struct Camera {
            public:
                enum CameraEye : int {
                    m_eCameraEye_Left = 0,
                    m_eCameraEye_Right = 1,
                    m_eCameraEye_Center = 2,
                };

                auto WorldToScreenPoint(const Vector3& position, CameraEye eye) -> Vector3 {
                    return reinterpret_cast<Vector3(*)(Camera*, Vector3, CameraEye)>(methodAddress_[
                        "Camera.WorldToScreenPoint"])(this, position, eye);
                }

                auto ScreenToWorldPoint(const Vector3& position) -> Vector3 {
                    return reinterpret_cast<Vector3(*)(Camera*, Vector3)>(methodAddress_[
                        "Camera.ScreenToWorldPoint"])(this, position);
                }

                auto GetDepth() -> float {
                    return reinterpret_cast<float(*)(Camera*)>(methodAddress_["Camera.get_depth"])(this);
                }

                auto SetDepth(const float value) -> void {
                    return reinterpret_cast<void(*)(Camera*, float)>(methodAddress_["Camera.set_depth"])(this, value);
                }

                static auto GetMain() -> Camera* {
                    return reinterpret_cast<Camera * (*)()>(methodAddress_["Camera.get_main"])();
                }

                static auto GetCurrent() -> Camera* {
                    return reinterpret_cast<Camera * (*)()>(methodAddress_["Camera.get_current"])();
                }

                static auto GetCameraCount() -> size_t {
                    return reinterpret_cast<size_t(*)()>(methodAddress_["Camera.get_allCamerasCount"])();
                }

                static auto GetAllCamera() -> Array<Camera>& {
                    return reinterpret_cast<Array<Camera>&(*)()>(methodAddress_["Camera.get_allCameras"])();
                }
            };

            struct Transform {
            public:
                auto GetPosition() -> Vector3 {
                    return reinterpret_cast<Vector3(*)(void*)>(methodAddress_["Transform.get_position"])(this);
                }

                auto SetPosition(Vector3 v) -> void {
                    return reinterpret_cast<void(*)(void*, Vector3)>(methodAddress_["Transform.get_position"])(this, v);
                }
            };

            struct GameObject {
            public:
                Transform* GetTransform() {
                    return reinterpret_cast<Transform*(*)(void*)>(methodAddress_["GameObject.get_transform"])(this);
                }

                String* GetTag() {
                    return reinterpret_cast<String * (*)(void*)>(methodAddress_["GameObject.get_tag"])(this);
                }
            };

            struct Component {
                Transform* GetTransform() {
                    return reinterpret_cast<Transform * (*)(void*)>(methodAddress_["Component.get_transform"])(this);
                }

                String* GetTag() {
                    return reinterpret_cast<String * (*)(void*)>(methodAddress_["Component.get_tag"])(this);
                }
            };
        };

        static auto SetIL2cppMod() -> void { il2cpp = true; }

        static auto SetMap(std::unordered_map<std::string, void*>& map) -> void;

    private:
        inline static bool                                            il2cpp{ false };
        inline static std::unordered_map<std::string, void*>* address_;
        inline static std::unordered_map<std::string, std::uintptr_t> methodAddress_;
    };

    class Mono {
    public:
        struct Domain;
        struct Assembly;
        struct Type;
        struct Table;
        struct Image;
        struct Class;
        struct Field;
        struct Method;
        struct VTable;
        struct MethodSignature;

    public:
        static auto SetModule(const HMODULE hModule) -> void {
            std::ofstream(stdout) << \
                R"(      ___           ___                       ___           ___                    ___           ___           ___           ___     )" << "\n" << \
                R"(     /\__\         /\__\          ___        /\  \         |\__\                  /\__\         /\  \         /\  \         /\__\    )" << "\n" << \
                R"(    /:/  /        /::|  |        /\  \       \:\  \        |:|  |                /:/  /        /::\  \       /::\  \       /:/  /    )" << "\n" << \
                R"(   /:/  /        /:|:|  |        \:\  \       \:\  \       |:|  |               /:/__/        /:/\:\  \     /:/\:\  \     /:/__/     )" << "\n" << \
                R"(  /:/  /  ___   /:/|:|  |__      /::\__\      /::\  \      |:|__|__            /::\  \ ___   /::\~\:\  \   /:/  \:\  \   /::\__\____ )" << "\n" << \
                R"( /:/__/  /\__\ /:/ |:| /\__\  __/:/\/__/     /:/\:\__\     /::::\__\          /:/\:\  /\__\ /:/\:\ \:\__\ /:/__/ \:\__\ /:/\:::::\__\)" << "\n" << \
                R"( \:\  \ /:/  / \/__|:|/:/  / /\/:/  /       /:/  \/__/    /:/~~/~             \/__\:\/:/  / \/__\:\/:/  / \:\  \  \/__/ \/_|:|~~|~   )" << "\n" << \
                R"(  \:\  /:/  /      |:/:/  /  \::/__/       /:/  /        /:/  /                    \::/  /       \::/  /   \:\  \          |:|  |    )" << "\n" << \
                R"(   \:\/:/  /       |::/  /    \:\__\       \/__/         \/__/                     /:/  /        /:/  /     \:\  \         |:|  |    )" << "\n" << \
                R"(    \::/  /        /:/  /      \/__/                                              /:/  /        /:/  /       \:\__\        |:|  |    )" << "\n" << \
                R"(     \/__/         \/__/                                                          \/__/         \/__/         \/__/         \|__|    )" << "\n" << \
                R"(                                                                                                                                     )" << "\n" << \
                R"(=====================================================================================================================================)" << "\n" << \
                R"(Unity Hack Library By 遂沫 2023/8/25 Mode: IL2CPP)" << "\n" << std::endl;

            hModule_ = hModule;
            size_t errorNum = 0, i = 0, max_ = address_.size();
            for (auto& [name, address] : address_) {
                address = static_cast<void*>(GetProcAddress(hModule, name.c_str()));
                if (!address) {
                    errorNum++;
                    LOG_WARNING(std::format("无法获取API \"{}\" 地址 \n", name));
                    continue;
                }
                LOG_DEBUG(std::format("\r [{:04d}|{:04d}] 获取API \"{}\" 地址: {:#010X}", ++i, max_, name, reinterpret_cast<std::uintptr_t>(address)));
            }
            if (errorNum != 0)
                LOG_WARNING(std::format("\n无法获取API数量：{} \n", errorNum));

            const auto domain = Domain::GetRoot();
            LOG_DEBUG(std::format("Root Domain: {:#8X}\n", reinterpret_cast<std::uintptr_t>(domain)));
            LOG_DEBUG("mono_thread_attach...\n");
            static_cast<Domain* (*)(Domain * domain)>(address_["mono_thread_attach"])(domain);
            LOG_DEBUG("mono_jit_thread_attach...\n");
            static_cast<Domain* (*)(Domain * domain)>(address_["mono_jit_thread_attach"])(domain);
            LOG_DEBUG("获取Unity函数...\n");
            CSharper::SetMap(address_);
            LOG_DEBUG("Mono运行时加载完成!\n");
        }

        static auto Dump(const std::string& file) -> void {
            std::ofstream io(file + "\\dump.cs", std::fstream::out);

            io << \
                "/*" << "\n" << \
                R"(*      ___           ___                       ___           ___                    ___           ___           ___           ___     )" << "\n" << \
                R"(*     /\__\         /\__\          ___        /\  \         |\__\                  /\__\         /\  \         /\  \         /\__\    )" << "\n" << \
                R"(*    /:/  /        /::|  |        /\  \       \:\  \        |:|  |                /:/  /        /::\  \       /::\  \       /:/  /    )" << "\n" << \
                R"(*   /:/  /        /:|:|  |        \:\  \       \:\  \       |:|  |               /:/__/        /:/\:\  \     /:/\:\  \     /:/__/     )" << "\n" << \
                R"(*  /:/  /  ___   /:/|:|  |__      /::\__\      /::\  \      |:|__|__            /::\  \ ___   /::\~\:\  \   /:/  \:\  \   /::\__\____ )" << "\n" << \
                R"(* /:/__/  /\__\ /:/ |:| /\__\  __/:/\/__/     /:/\:\__\     /::::\__\          /:/\:\  /\__\ /:/\:\ \:\__\ /:/__/ \:\__\ /:/\:::::\__\)" << "\n" << \
                R"(* \:\  \ /:/  / \/__|:|/:/  / /\/:/  /       /:/  \/__/    /:/~~/~             \/__\:\/:/  / \/__\:\/:/  / \:\  \  \/__/ \/_|:|~~|~   )" << "\n" << \
                R"(*  \:\  /:/  /      |:/:/  /  \::/__/       /:/  /        /:/  /                    \::/  /       \::/  /   \:\  \          |:|  |    )" << "\n" << \
                R"(*   \:\/:/  /       |::/  /    \:\__\       \/__/         \/__/                     /:/  /        /:/  /     \:\  \         |:|  |    )" << "\n" << \
                R"(*    \::/  /        /:/  /      \/__/                                              /:/  /        /:/  /       \:\__\        |:|  |    )" << "\n" << \
                R"(*     \/__/         \/__/                                                          \/__/         \/__/         \/__/         \|__|    )" << "\n" << \
                R"(*                                                                                                                                     )" << "\n" << \
                R"(*=====================================================================================================================================)" << "\n" << \
                R"(*Unity Hack Library By 遂沫 2023/8/25 Mode: IL2CPP)" << "\n*/" << std::endl;

            size_t image_s{}, image_i{};
            std::list<Assembly*> assemblys;
            Assembly::EnumAssemblys(assemblys);
            image_s = assemblys.size();
            for (const auto& assembly : assemblys) {
                if (!assembly)
                    continue;

                Image* image_{};
                try {
                    image_ = assembly->GetImage();
                }
                catch (...) {
                    continue;
                }

                if (image_ == nullptr) {
                    continue;
                }

                int class_s{ 0 }, class_i{ 0 };
                try {
                    class_s = image_->GetClassCount();
                }
                catch (...) {
                    continue;
                }

                std::string image_name{};
                try {
                    image_name = image_->GetName();
                }
                catch (...) {
                    continue;
                }

                std::list<Class*> classes_;
                try {
                    image_->EnumClasses(classes_);
                }
                catch (...) {
                    continue;
                }

                for (auto& klass : classes_) {
                    if (klass == 0)
                        continue;

                    io << std::format("[{:04d}|{:04d}] {} \n", ++image_i, image_s, image_name);
                    io << std::format("using namespace {};\n", klass->GetNamespace());
                    io << std::format("[{:04d}|{:04d}] class {} {}\n", ++class_i, class_s, klass->GetName(), klass->GetParent() ? ": " + klass->GetParent()->GetName() : "");
                    io << "{\n";

                    int field_i{ 0 }, method_i{ 0 };
                    std::list<Field*> fields_;
                    klass->EnumFields(fields_);
                    std::list<Method*> methods_;
                    klass->EnumMethods(methods_);

                    io << std::format("    // 变量 -count:{}\n", fields_.size());
                    for (auto& field : fields_) {
                        if (!field)
                            continue;
                        io << std::format("    [{:04d}|{:04d}] |Offset: {:+#06X}| {} {} {};\n", ++field_i, fields_.size(), field->GetOffset(), field->IsStatic() ? "static" : "      ", field->GetType()->GetName(), field->GetName());
                    }

                    io << std::format("\n    // 函数 -count:{}\n", methods_.size());
                    for (auto& method : methods_) {
                        if (!method)
                            continue;
                        io << std::format("    [Flags: {:032b}] [ParamCount: {:04d}]\n    [{:04d}|{:04d}] |RVA: {:+#010X}| {} {} {}(",
                            method->GetFlags(), method->GetParamCount(), ++method_i, methods_.size(), method->GetAddress() - reinterpret_cast<std::uintptr_t>(hModule_),
                            method->IsStatic() ? "static" : "      ", method->GetRetType()->GetName(), method->GetName());

                        std::map<std::string, Type*> map_;
                        method->EnumParam(map_);
                        for (auto& [name, type] : map_) {
                            if (!type)
                                continue;
                            io << std::format("{} {}, ", type->GetName(), name);
                        }

                        if (map_.size() > 0) {
                            io.seekp(-1, std::ios_base::end);
                            io << "";
                            io.seekp(-1, std::ios_base::end);
                            io << "";
                        }

                        io << ");\n\n";
                    }

                    io << "} // Dump Tool By 遂沫 2023 \n";
                }
            }
            io.close();
            SetFileAttributesA((file + "\\dump.cs").c_str(), FILE_ATTRIBUTE_READONLY);
            SetFileAttributesA((file + "\\dump.cs").c_str(), FILE_ATTRIBUTE_SYSTEM);
        }

        struct Domain {
        public:
            static auto EnumDomains(std::list<Domain*>& domains) -> size_t {
                static_cast<void(*)(void(__cdecl * func)(Domain * data, std::list<Domain*>&user_data), std::list<Domain*>&user_data)>(address_["mono_domain_foreach"])([](Domain* ptr, std::list<Domain*>& v) { v.push_back(ptr); }, domains);
                return domains.size();
            }
            static auto GetRoot() -> Domain* { return static_cast<Domain * (*)()>(address_["mono_get_root_domain"])(); }
        };

        struct Assembly {
        public:
            static auto EnumAssemblys(std::list<Assembly*>& assembly) -> size_t {
                static_cast<void(*)(void(__cdecl * func)(Assembly * data, std::list<Assembly*>&user_data), std::list<Assembly*>&user_data)>(address_["mono_assembly_foreach"])([](Assembly* ptr, std::list<Assembly*>& v) { v.push_back(ptr); },assembly);
                return assembly.size();
            }

            auto GetImage() -> Image* {
                try {
                    return static_cast<Image * (*)(Assembly * assembly)>(address_["mono_assembly_get_image"])(this);
                } catch (...) {
                    return nullptr;
                }
            }

            auto GetName() -> std::string {
                try {
                    return static_cast<const char* (*)(Assembly * _this)>(address_["mono_assembly_get_name"])(this);
                } catch (...) {
                    return "";
                }
            }
        };

        struct Type {
        public:
            auto GetName() -> std::string {
                try {
                    return static_cast<const char* (*)(Type * type)>(address_["mono_type_get_name"])(this);
                } catch (...) {
                    return "";
                }
            }

            auto GetSize() -> size_t {
                try {
                    size_t bytes{};
                    return static_cast<size_t(*)(Type * type, size_t * size)>(address_["mono_type_size"])(this, &bytes);
                } catch (...) {
                    return 0;
                }
            }
        };

        struct Table {
        public:
            const char* base;
            std::uint32_t rows : 24;
            std::uint32_t row_size : 8;

            /*
             * Tables contain up to 9 columns and the possible sizes of the
             * fields in the documentation are 1, 2 and 4 bytes.  So we
             * can encode in 2 bits the size.
             *
             * A 32 bit value can encode the resulting size
             *
             * The top eight bits encode the number of columns in the table.
             * we only need 4, but 8 is aligned no shift required.
             */
            std::uint32_t size_bitfield;

            auto GetRows() -> size_t {
                try {
                    return static_cast<int(*)(Table * _this)>(address_["mono_table_info_get_rows"])(this);
                } catch (...) {
                    return 0;
                }
            }
        };

        struct Image {
        public:
            auto GetName() -> std::string {
                try {
                    return static_cast<const char* (*)(Image * _this)>(address_["mono_image_get_name"])(this);
                } catch (...) {
                    return "";
                }
            }

            auto GetFile() -> std::string {
                try {
                    return static_cast<const char* (*)(Image * _this)>(address_["mono_image_get_filename"])(this);
                } catch (...) {
                    return "";
                }
            }

            auto EnumClasses(std::list<Class*>& classes) -> size_t {
                try {
                    const auto table = static_cast<Table * (*)(Image * _this, int id)>(address_["mono_image_get_table_info"])(this, 2);
                    const size_t count = table->GetRows();
                    for (size_t i = 0; i < count; i++) {
                        auto class_ = static_cast<Class * (*)(Image * _this, size_t index)>(address_["mono_class_get"])(this, 0x02000000 | (i + 1));
                        if (class_)classes.push_back(class_);
                    }
                    return classes.size();
                } catch (...) {
                    return classes.size();
                }
            }

            auto GetClassCount() -> size_t {
                try {
                    const auto table = static_cast<Table * (*)(Image * _this, int id)>(address_["mono_image_get_table_info"])(this, 2);
                    return table->GetRows();
                } catch (...) {
                    return 0;
                }
            }

            auto GetClassFromName(const std::string& name, const std::string& name_space = "") -> Class* {
                std::list<Class*> classes;
                this->EnumClasses(classes);
                for (const auto& klass : classes) {
                    if (klass == nullptr)
                        continue;
                    if (klass->GetName() != name)
                        continue;
                    if (!name_space.empty())
                        if (klass->GetNamespace() != name_space)
                            continue;
                    return klass;
                }
                return nullptr;
            }
        };

        struct Class {
        public:
            auto GetName() -> std::string {
                try {
                    return static_cast<const char* (*)(Class * _this)>(address_["mono_class_get_name"])(this);
                } catch (...) {
                    return "";
                }
            }

            auto GetNamespace() -> std::string {
                try {
                    return static_cast<const char* (*)(Class * _this)>(address_["mono_class_get_namespace"])(this);
                } catch (...) {
                    return "";
                }
            }

            auto GetParent() -> Class* {
                try {
                    return static_cast<Class * (*)(Class * _this)>(address_["mono_class_get_parent"])(this);
                } catch (...) {
                    return nullptr;
                }
            }

            auto EnumFields(std::list<Field*>& fields) -> size_t {
                void* iter = nullptr;
                Field* field;
                do {
                    try {
                        field = static_cast<Field * (*)(Class * _this, void* iter)>(address_["mono_class_get_fields"])(this, &iter);
                        if (field)
                            fields.push_back(field);
                    } catch (...) {
                        field = 0;
                        continue;
                    }
                } while (field);
                return fields.size();
            }

            auto GetFieldFromName(const std::string& name) -> Field* {
                try {
                    return static_cast<Field * (*)(Class * _this, const char* name)>(address_["mono_class_get_field_from_name"])(this, name.c_str());
                } catch (...) {
                    return nullptr;
                }
            }

            auto EnumMethods(std::list<Method*>& methods) -> size_t {
                void* iter = nullptr;
                Method* field;
                do {
                    try {
                        field = static_cast<Method * (*)(Class * _this, void* iter)>(address_["mono_class_get_methods"])(this, &iter);
                        if (field)
                            methods.push_back(field);
                    } catch (...) {
                        field = 0;
                        continue;
                    }
                } while (field);
                return methods.size();
            }

            auto GetMethodFromName(const std::string& name, const size_t param_count = -1) -> Method* {
                try {
                    return static_cast<Method * (*)(Class * _this, const char* name, size_t param_count)>(address_["mono_class_get_method_from_name"])(this, name.c_str(), param_count);
                } catch (...) {
                    return nullptr;
                }
            }

            auto GetType() -> Type* {
                return static_cast<Type * (*)(Class * _this)>(address_["mono_class_get_type"])(this);
            }

            static auto GetClassFromName(const std::string& class_name, const std::string& namespaze = "") -> Class* {
                std::list<Assembly*> assemblys;
                Assembly::EnumAssemblys(assemblys);
                for (const auto& assembly : assemblys) {
                    Class* klass{};
                    try {
                        klass = assembly->GetImage()->GetClassFromName(class_name, namespaze);
                    }
                    catch (...) {
                        LOG_WARNING(std::format("assembly异常"));
                        continue;
                    }

                    if (klass == nullptr)
                        continue;
                    if (klass->GetName() != class_name)
                        continue;
                    if (namespaze != "")
                        if (klass->GetNamespace() != namespaze)
                            continue;

                    return klass;
                }
                return nullptr;
            }
        };

        struct Field {
        public:
            /* Type of the field */
            Type* type;

            const char* name;

            /* Type where the field was defined */
            Class* parent;

            /*
             * Offset where this field is stored; if it is an instance
             * field, it's the offset from the start of the object, if
             * it's static, it's from the start of the memory chunk
             * allocated for statics for the class.
             * For special static fields, this is set to -1 during vtable construction.
             */
            int offset;

            template<typename T>
            auto GetStatic() -> T {
                try {
                    T          val = 0;
                    const auto vtable = static_cast<VTable * (*)(Domain * domain, Class * klass)>(address_["mono_class_vtable"])(Domain::GetRoot(), this->parent);
                    static_cast<void(*)(VTable * vt, Field * field, void* ptr)>(address_["mono_field_static_get_value"])(vtable, this, &val);
                    return val;
                } catch (...) {
                    return T{};
                }
            }

            template<typename T>
            auto SetStatic(T& val) -> void {
                try {
                    const auto vtable = static_cast<VTable * (*)(Domain * domain, Class * klass)>(address_["mono_class_vtable"])(Domain::GetRoot(), this->parent);
                    static_cast<void(*)(VTable * vt, Field * field, void* ptr)>(address_["mono_field_static_set_value"])(vtable, this, &val);
                } catch (...) {
                    return;
                }
            }

            auto IsStatic() const -> bool {
                try {
                    return this->offset == -1 ? true : false;
                } catch (...) {
                    return false;
                }
            }

            auto GetName() -> std::string {
                try {
                    return static_cast<const char* (*)(Field * _this)>(address_["mono_field_get_name"])(this);
                } catch (...) {
                    return "";
                }
            }

            auto GetType() -> Type* {
                try {
                    return static_cast<Type * (*)(Field * _this)>(address_["mono_field_get_type"])(this);
                } catch (...) {
                    return nullptr;
                }
            }

            auto GetOffset() -> std::uintptr_t {
                try {
                    return reinterpret_cast<std::uintptr_t>(static_cast<void* (*)(Field * _this)>(address_["mono_field_get_offset"])(this));
                } catch (...) {
                    return 0;
                }
            }
        };

        struct Method {
        public:
            std::uint16_t    flags;  /* method flags */
            std::uint16_t    iflags; /* method implementation flags */
            std::uint32_t    token;
            Class* klass; /* To what class does this method belong */
            MethodSignature* signature;
            /* name is useful mostly for debugging */
            const char* name;
            /* this is used by the inlining algorithm */
            unsigned int inline_info : 1;
            unsigned int inline_failure : 1;
            unsigned int wrapper_type : 5;
            unsigned int string_ctor : 1;
            unsigned int save_lmf : 1;
            unsigned int dynamic : 1; /* created & destroyed during runtime */
            unsigned int sre_method : 1; /* created at runtime using Reflection.Emit */
            unsigned int is_generic : 1; /* whenever this is a generic method definition */
            unsigned int is_inflated : 1; /* whether we're a MonoMethodInflated */
            unsigned int skip_visibility : 1; /* whenever to skip JIT visibility checks */
            unsigned int _unused : 2; /* unused */
            signed int   slot : 16;

            auto GetName() -> std::string {
                try {
                    return static_cast<const char* (*)(Method * _this)>(address_["mono_method_get_name"])(this);
                } catch (...) {
                    return "";
                }
            }

            auto GetRetType() -> Type* {
                try {
                    const auto signature = static_cast<void* (*)(Method * _this)>(address_["mono_method_signature"])(this);
                    return static_cast<Type * (*)(void* _this)>(address_["mono_signature_get_return_type"])(signature);
                } catch (...) {
                    return nullptr;
                }
            }

            auto GetParamCount() -> size_t {
                try {
                    const auto signature = static_cast<void* (*)(Method * _this)>(address_["mono_method_signature"])(this);
                    return static_cast<int(*)(void* _this)>(address_["mono_signature_get_param_count"])(signature);
                } catch (...) {
                    return 0;
                }
            }

            auto GetParam(const size_t index) -> Type* {
                auto  i = 0;
                void* iter = nullptr;
                Type* type;
                do {
                    try {
                        type = static_cast<Type * (*)(void* _this, void* iter)>(address_["mono_signature_get_params"])(this, &iter);
                        if (i == index)
                            return type;
                        i++;
                    } catch (...) {
                        type = 0;
                        continue;
                    }
                } while (type);
                return nullptr;
            }

            auto GetFlags() const -> std::uint32_t {
                try {
                    return reinterpret_cast<std::uint32_t(*)(const Method*, uint32_t*)>(address_["mono_method_get_flags"])(this, nullptr);
                }
                catch (...) {
                    return 0;
                }
            }

            auto GetParamName(const size_t index) -> std::string {
                const auto names = new char* [GetParamCount()];
                try {
                    static_cast<void(*)(Method * _this, const char** str)>(address_["mono_method_get_param_names"])(this, const_cast<const char**>(names));
                    std::string name = names[index];
                    delete[] names;
                    return name;
                } catch (...) {
                    delete[] names;
                    return "";
                }
            }

            auto EnumParam(std::map<std::string, Type*>& map) -> size_t {
                try {
                    size_t count = this->GetParamCount();
                    for (size_t i = 0; i < count; i++)
                        map[this->GetParamName(i)] = this->GetParam(i);
                    return map.size();
                } catch (...) {
                    return map.size();
                }
            }

            auto IsStatic() const -> bool {
                try {
                    return this->flags & 0x10;
                } catch (...) {
                    return false;
                }
            }

            template<typename OBJ>
            auto Invoke(OBJ* obj, void** params) -> struct Object* {
                try {
                    return static_cast<Object * (*)(Method * _this, void* obj, void** params, Object * *exc)>(address_["mono_runtime_invoke"])(this, obj, params, nullptr);
                } catch (...) {
                    return nullptr;
                }
            }

            auto GetAddress() -> std::uintptr_t {
                try {
                    return reinterpret_cast<std::uintptr_t>(static_cast<void* (*)(Method * _this)>(address_["mono_compile_method"])(this));
                } catch (...) {
                    return 0;
                }
            }

            static auto GetAddress(const std::string& class_name,
                const std::string& method_name,
                const size_t       param_count = -1,
                const std::string& namespaze = "") -> std::uintptr_t {
                Class* klass{};
                try {
                    klass = Class::GetClassFromName(class_name, namespaze);
                    if (klass == nullptr) {
                        LOG_WARNING(std::format("未找到 \"{}\" 类", class_name));
                        return 0;
                    }
                }
                catch (...) {
                    LOG_WARNING(std::format("寻找 \"{}\" 类时发生异常", class_name));
                    return 0;
                }

                try {
                    return klass->GetMethodFromName(method_name, param_count)->GetAddress();
                }
                catch (...) {
                    LOG_WARNING(std::format("未找到 \"{}\" 函数", method_name));
                    return 0;
                }
            }
        };

    private:
        inline static HMODULE                                hModule_;
        inline static std::unordered_map<std::string, void*> address_{
            {"GC_dirty_inner", nullptr}, {"GC_free", nullptr}, {"GC_gcj_malloc", nullptr},
            {"GC_make_descriptor", nullptr}, {"GC_malloc", nullptr}, {"GC_malloc_atomic", nullptr},
            {"GC_malloc_kind", nullptr}, {"GC_malloc_uncollectable", nullptr}, {"MonoFixupCorEE", nullptr},
            {"mini_get_debug_options", nullptr}, {"mini_parse_debug_option", nullptr},
            {"mono_add_internal_call", nullptr}, {"mono_aot_register_module", nullptr},
            {"mono_array_addr_with_size", nullptr}, {"mono_array_class_get", nullptr}, {"mono_array_clone", nullptr},
            {"mono_array_element_size", nullptr}, {"mono_array_length", nullptr}, {"mono_array_new", nullptr},
            {"mono_array_new_full", nullptr}, {"mono_array_new_specific", nullptr},
            {"mono_assemblies_cleanup", nullptr}, {"mono_assemblies_init", nullptr}, {"mono_assembly_addref", nullptr},
            {"mono_assembly_close", nullptr}, {"mono_assembly_fill_assembly_name", nullptr},
            {"mono_assembly_foreach", nullptr}, {"mono_assembly_get_assemblyref", nullptr},
            {"mono_assembly_get_image", nullptr}, {"mono_assembly_get_main", nullptr},
            {"mono_assembly_get_name", nullptr}, {"mono_assembly_get_object", nullptr},
            {"mono_assembly_getrootdir", nullptr}, {"mono_assembly_invoke_load_hook", nullptr},
            {"mono_assembly_invoke_search_hook", nullptr}, {"mono_assembly_load", nullptr},
            {"mono_assembly_load_from", nullptr}, {"mono_assembly_load_from_full", nullptr},
            {"mono_assembly_load_full", nullptr}, {"mono_assembly_load_module", nullptr},
            {"mono_assembly_load_module_checked", nullptr}, {"mono_assembly_load_reference", nullptr},
            {"mono_assembly_load_references", nullptr}, {"mono_assembly_load_with_partial_name", nullptr},
            {"mono_assembly_loaded", nullptr}, {"mono_assembly_loaded_full", nullptr},
            {"mono_assembly_name_free", nullptr}, {"mono_assembly_name_get_culture", nullptr},
            {"mono_assembly_name_get_name", nullptr}, {"mono_assembly_name_get_pubkeytoken", nullptr},
            {"mono_assembly_name_get_version", nullptr}, {"mono_assembly_name_new", nullptr},
            {"mono_assembly_name_parse", nullptr}, {"mono_assembly_names_equal", nullptr},
            {"mono_assembly_open", nullptr}, {"mono_assembly_open_full", nullptr}, {"mono_assembly_set_main", nullptr},
            {"mono_assembly_setrootdir", nullptr}, {"mono_bitset_alloc_size", nullptr}, {"mono_bitset_clear", nullptr},
            {"mono_bitset_clear_all", nullptr}, {"mono_bitset_clone", nullptr}, {"mono_bitset_copyto", nullptr},
            {"mono_bitset_count", nullptr}, {"mono_bitset_equal", nullptr}, {"mono_bitset_find_first", nullptr},
            {"mono_bitset_find_first_unset", nullptr}, {"mono_bitset_find_last", nullptr},
            {"mono_bitset_find_start", nullptr}, {"mono_bitset_foreach", nullptr}, {"mono_bitset_free", nullptr},
            {"mono_bitset_intersection", nullptr}, {"mono_bitset_intersection_2", nullptr},
            {"mono_bitset_invert", nullptr}, {"mono_bitset_mem_new", nullptr}, {"mono_bitset_new", nullptr},
            {"mono_bitset_set", nullptr}, {"mono_bitset_set_all", nullptr}, {"mono_bitset_size", nullptr},
            {"mono_bitset_sub", nullptr}, {"mono_bitset_test", nullptr}, {"mono_bitset_test_bulk", nullptr},
            {"mono_bitset_union", nullptr}, {"mono_bounded_array_class_get", nullptr},
            {"mono_breakpoint_clean_code", nullptr}, {"mono_build_date", nullptr}, {"mono_callspec_cleanup", nullptr},
            {"mono_callspec_eval", nullptr}, {"mono_callspec_eval_exception", nullptr},
            {"mono_callspec_parse", nullptr}, {"mono_check_corlib_version", nullptr},
            {"mono_class_array_element_size", nullptr}, {"mono_class_data_size", nullptr},
            {"mono_class_describe_statics", nullptr}, {"mono_class_enum_basetype", nullptr},
            {"mono_class_from_generic_parameter", nullptr}, {"mono_class_from_mono_type", nullptr},
            {"mono_class_from_name", nullptr}, {"mono_class_from_name_case", nullptr},
            {"mono_class_from_typeref", nullptr}, {"mono_class_from_typeref_checked", nullptr},
            {"mono_class_get", nullptr}, {"mono_class_get_byref_type", nullptr}, {"mono_class_get_context", nullptr},
            {"mono_class_get_element_class", nullptr}, {"mono_class_get_event_token", nullptr},
            {"mono_class_get_events", nullptr}, {"mono_class_get_field", nullptr},
            {"mono_class_get_field_from_name", nullptr}, {"mono_class_get_field_token", nullptr},
            {"mono_class_get_fields", nullptr}, {"mono_class_get_flags", nullptr}, {"mono_class_get_full", nullptr},
            {"mono_class_get_image", nullptr}, {"mono_class_get_interfaces", nullptr},
            {"mono_class_get_method_from_name", nullptr}, {"mono_class_get_method_from_name_flags", nullptr},
            {"mono_class_get_methods", nullptr}, {"mono_class_get_name", nullptr},
            {"mono_class_get_namespace", nullptr}, {"mono_class_get_nested_types", nullptr},
            {"mono_class_get_nesting_type", nullptr}, {"mono_class_get_parent", nullptr},
            {"mono_class_get_properties", nullptr}, {"mono_class_get_property_from_name", nullptr},
            {"mono_class_get_property_token", nullptr}, {"mono_class_get_rank", nullptr},
            {"mono_class_get_type", nullptr}, {"mono_class_get_type_token", nullptr},
            {"mono_class_get_userdata", nullptr}, {"mono_class_get_userdata_offset", nullptr},
            {"mono_class_implements_interface", nullptr}, {"mono_class_inflate_generic_method", nullptr},
            {"mono_class_inflate_generic_type", nullptr}, {"mono_class_init", nullptr},
            {"mono_class_instance_size", nullptr}, {"mono_class_interface_offset", nullptr},
            {"mono_class_is_assignable_from", nullptr}, {"mono_class_is_blittable", nullptr},
            {"mono_class_is_delegate", nullptr}, {"mono_class_is_enum", nullptr}, {"mono_class_is_generic", nullptr},
            {"mono_class_is_inflated", nullptr}, {"mono_class_is_subclass_of", nullptr},
            {"mono_class_is_valid_enum", nullptr}, {"mono_class_is_valuetype", nullptr},
            {"mono_class_min_align", nullptr}, {"mono_class_name_from_token", nullptr},
            {"mono_class_num_events", nullptr}, {"mono_class_num_fields", nullptr}, {"mono_class_num_methods", nullptr},
            {"mono_class_num_properties", nullptr}, {"mono_class_set_userdata", nullptr},
            {"mono_class_value_size", nullptr}, {"mono_class_vtable", nullptr}, {"mono_cli_rva_image_map", nullptr},
            {"mono_code_manager_cleanup", nullptr}, {"mono_code_manager_commit", nullptr},
            {"mono_code_manager_destroy", nullptr}, {"mono_code_manager_init", nullptr},
            {"mono_code_manager_install_callbacks", nullptr}, {"mono_code_manager_invalidate", nullptr},
            {"mono_code_manager_new", nullptr}, {"mono_code_manager_new_dynamic", nullptr},
            {"mono_code_manager_reserve", nullptr}, {"mono_code_manager_reserve_align", nullptr},
            {"mono_code_manager_set_read_only", nullptr}, {"mono_code_manager_size", nullptr},
            {"mono_compile_method", nullptr}, {"mono_conc_hashtable_destroy", nullptr},
            {"mono_conc_hashtable_foreach", nullptr}, {"mono_conc_hashtable_foreach_steal", nullptr},
            {"mono_conc_hashtable_insert", nullptr}, {"mono_conc_hashtable_lookup", nullptr},
            {"mono_conc_hashtable_new", nullptr}, {"mono_conc_hashtable_new_full", nullptr},
            {"mono_conc_hashtable_remove", nullptr}, {"mono_config_cleanup", nullptr},
            {"mono_config_for_assembly", nullptr}, {"mono_config_get_cpu", nullptr}, {"mono_config_get_os", nullptr},
            {"mono_config_get_wordsize", nullptr}, {"mono_config_is_server_mode", nullptr},
            {"mono_config_parse", nullptr}, {"mono_config_parse_memory", nullptr},
            {"mono_config_set_server_mode", nullptr}, {"mono_config_string_for_assembly_file", nullptr},
            {"mono_context_get", nullptr}, {"mono_context_get_desc", nullptr}, {"mono_context_get_domain_id", nullptr},
            {"mono_context_get_id", nullptr}, {"mono_context_init", nullptr}, {"mono_context_set", nullptr},
            {"mono_counter_get_name", nullptr}, {"mono_counter_get_section", nullptr},
            {"mono_counter_get_size", nullptr}, {"mono_counter_get_type", nullptr}, {"mono_counter_get_unit", nullptr},
            {"mono_counter_get_variance", nullptr}, {"mono_counters_cleanup", nullptr}, {"mono_counters_dump", nullptr},
            {"mono_counters_enable", nullptr}, {"mono_counters_foreach", nullptr}, {"mono_counters_init", nullptr},
            {"mono_counters_on_register", nullptr}, {"mono_counters_register", nullptr},
            {"mono_counters_register_with_size", nullptr}, {"mono_counters_sample", nullptr},
            {"mono_cpu_count", nullptr}, {"mono_custom_attrs_construct", nullptr},
            {"mono_custom_attrs_construct_by_type", nullptr}, {"mono_custom_attrs_free", nullptr},
            {"mono_custom_attrs_from_assembly", nullptr}, {"mono_custom_attrs_from_class", nullptr},
            {"mono_custom_attrs_from_event", nullptr}, {"mono_custom_attrs_from_field", nullptr},
            {"mono_custom_attrs_from_index", nullptr}, {"mono_custom_attrs_from_method", nullptr},
            {"mono_custom_attrs_from_param", nullptr}, {"mono_custom_attrs_from_property", nullptr},
            {"mono_custom_attrs_get_attr", nullptr}, {"mono_custom_attrs_get_attrs", nullptr},
            {"mono_custom_attrs_has_attr", nullptr}, {"mono_debug_add_delegate_trampoline", nullptr},
            {"mono_debug_add_method", nullptr}, {"mono_debug_cleanup", nullptr}, {"mono_debug_close_image", nullptr},
            {"mono_debug_close_mono_symbol_file", nullptr}, {"mono_debug_domain_create", nullptr},
            {"mono_debug_domain_unload", nullptr}, {"mono_debug_enabled", nullptr}, {"mono_debug_find_method", nullptr},
            {"mono_debug_free_locals", nullptr}, {"mono_debug_free_method_jit_info", nullptr},
            {"mono_debug_free_source_location", nullptr}, {"mono_debug_il_offset_from_address", nullptr},
            {"mono_debug_init", nullptr}, {"mono_debug_lookup_locals", nullptr}, {"mono_debug_lookup_method", nullptr},
            {"mono_debug_lookup_method_addresses", nullptr}, {"mono_debug_lookup_source_location", nullptr},
            {"mono_debug_lookup_source_location_by_il", nullptr}, {"mono_debug_open_image_from_memory", nullptr},
            {"mono_debug_open_mono_symbols", nullptr}, {"mono_debug_print_stack_frame", nullptr},
            {"mono_debug_print_vars", nullptr}, {"mono_debug_remove_method", nullptr},
            {"mono_debug_symfile_free_location", nullptr}, {"mono_debug_symfile_is_loaded", nullptr},
            {"mono_debug_symfile_lookup_locals", nullptr}, {"mono_debug_symfile_lookup_location", nullptr},
            {"mono_debug_symfile_lookup_method", nullptr}, {"mono_debugger_agent_parse_options", nullptr},
            {"mono_debugger_agent_register_transport", nullptr}, {"mono_debugger_agent_transport_handshake", nullptr},
            {"mono_debugger_disconnect", nullptr}, {"mono_debugger_get_generate_debug_info", nullptr},
            {"mono_debugger_insert_breakpoint", nullptr}, {"mono_debugger_install_attach_detach_callback", nullptr},
            {"mono_debugger_method_has_breakpoint", nullptr}, {"mono_debugger_run_finally", nullptr},
            {"mono_debugger_set_generate_debug_info", nullptr}, {"mono_declsec_flags_from_assembly", nullptr},
            {"mono_declsec_flags_from_class", nullptr}, {"mono_declsec_flags_from_method", nullptr},
            {"mono_declsec_get_assembly_action", nullptr}, {"mono_declsec_get_class_action", nullptr},
            {"mono_declsec_get_demands", nullptr}, {"mono_declsec_get_inheritdemands_class", nullptr},
            {"mono_declsec_get_inheritdemands_method", nullptr}, {"mono_declsec_get_linkdemands", nullptr},
            {"mono_declsec_get_method_action", nullptr}, {"mono_digest_get_public_token", nullptr},
            {"mono_disasm_code", nullptr}, {"mono_disasm_code_one", nullptr}, {"mono_dl_fallback_register", nullptr},
            {"mono_dl_fallback_unregister", nullptr}, {"mono_dl_open", nullptr}, {"mono_dllmap_insert", nullptr},
            {"mono_domain_assembly_foreach", nullptr}, {"mono_domain_assembly_open", nullptr},
            {"mono_domain_create", nullptr}, {"mono_domain_create_appdomain", nullptr},
            {"mono_domain_finalize", nullptr}, {"mono_domain_foreach", nullptr}, {"mono_domain_free", nullptr},
            {"mono_domain_from_appdomain", nullptr}, {"mono_domain_get", nullptr}, {"mono_domain_get_by_id", nullptr},
            {"mono_domain_get_friendly_name", nullptr}, {"mono_domain_get_id", nullptr},
            {"mono_domain_has_type_resolve", nullptr}, {"mono_domain_is_unloading", nullptr},
            {"mono_domain_jit_foreach", nullptr}, {"mono_domain_owns_vtable_slot", nullptr},
            {"mono_domain_set", nullptr}, {"mono_domain_set_config", nullptr}, {"mono_domain_set_internal", nullptr},
            {"mono_domain_try_type_resolve", nullptr}, {"mono_domain_try_unload", nullptr},
            {"mono_domain_unload", nullptr}, {"mono_environment_exitcode_get", nullptr},
            {"mono_environment_exitcode_set", nullptr}, {"mono_error_cleanup", nullptr},
            {"mono_error_get_error_code", nullptr}, {"mono_error_get_message", nullptr}, {"mono_error_init", nullptr},
            {"mono_error_init_flags", nullptr}, {"mono_error_ok", nullptr}, {"mono_escape_uri_string", nullptr},
            {"mono_event_get_add_method", nullptr}, {"mono_event_get_flags", nullptr}, {"mono_event_get_name", nullptr},
            {"mono_event_get_object", nullptr}, {"mono_event_get_parent", nullptr},
            {"mono_event_get_raise_method", nullptr}, {"mono_event_get_remove_method", nullptr},
            {"mono_exception_from_name", nullptr}, {"mono_exception_from_name_domain", nullptr},
            {"mono_exception_from_name_msg", nullptr}, {"mono_exception_from_name_two_strings", nullptr},
            {"mono_exception_from_token", nullptr}, {"mono_exception_from_token_two_strings", nullptr},
            {"mono_exception_walk_trace", nullptr}, {"mono_field_from_token", nullptr},
            {"mono_field_full_name", nullptr}, {"mono_field_get_data", nullptr}, {"mono_field_get_flags", nullptr},
            {"mono_field_get_name", nullptr}, {"mono_field_get_object", nullptr}, {"mono_field_get_offset", nullptr},
            {"mono_field_get_parent", nullptr}, {"mono_field_get_type", nullptr}, {"mono_field_get_value", nullptr},
            {"mono_field_get_value_object", nullptr}, {"mono_field_set_value", nullptr},
            {"mono_field_static_get_value", nullptr}, {"mono_field_static_set_value", nullptr},
            {"mono_file_map", nullptr}, {"mono_file_map_close", nullptr}, {"mono_file_map_fd", nullptr},
            {"mono_file_map_open", nullptr}, {"mono_file_map_size", nullptr}, {"mono_file_unmap", nullptr},
            {"mono_free", nullptr}, {"mono_free_bstr", nullptr}, {"mono_free_method", nullptr},
            {"mono_free_verify_list", nullptr}, {"mono_g_hash_table_destroy", nullptr},
            {"mono_g_hash_table_find", nullptr}, {"mono_g_hash_table_foreach", nullptr},
            {"mono_g_hash_table_foreach_remove", nullptr}, {"mono_g_hash_table_insert", nullptr},
            {"mono_g_hash_table_lookup", nullptr}, {"mono_g_hash_table_lookup_extended", nullptr},
            {"mono_g_hash_table_new_type", nullptr}, {"mono_g_hash_table_print_stats", nullptr},
            {"mono_g_hash_table_remove", nullptr}, {"mono_g_hash_table_replace", nullptr},
            {"mono_g_hash_table_size", nullptr}, {"mono_gc_collect", nullptr}, {"mono_gc_collect_a_little", nullptr},
            {"mono_gc_collection_count", nullptr}, {"mono_gc_finalize_notify", nullptr},
            {"mono_gc_get_generation", nullptr}, {"mono_gc_get_heap_size", nullptr},
            {"mono_gc_get_max_time_slice_ns", nullptr}, {"mono_gc_get_used_size", nullptr},
            {"mono_gc_invoke_finalizers", nullptr}, {"mono_gc_is_incremental", nullptr},
            {"mono_gc_max_generation", nullptr}, {"mono_gc_pending_finalizers", nullptr},
            {"mono_gc_reference_queue_add", nullptr}, {"mono_gc_reference_queue_free", nullptr},
            {"mono_gc_reference_queue_new", nullptr}, {"mono_gc_register_finalizer_callbacks", nullptr},
            {"mono_gc_register_root", nullptr}, {"mono_gc_set_incremental", nullptr},
            {"mono_gc_set_max_time_slice_ns", nullptr}, {"mono_gc_start_incremental_collection", nullptr},
            {"mono_gc_toggleref_add", nullptr}, {"mono_gc_toggleref_register_callback", nullptr},
            {"mono_gc_walk_heap", nullptr}, {"mono_gc_wbarrier_arrayref_copy", nullptr},
            {"mono_gc_wbarrier_generic_nostore", nullptr}, {"mono_gc_wbarrier_generic_store", nullptr},
            {"mono_gc_wbarrier_generic_store_atomic", nullptr}, {"mono_gc_wbarrier_object_copy", nullptr},
            {"mono_gc_wbarrier_set_arrayref", nullptr}, {"mono_gc_wbarrier_set_field", nullptr},
            {"mono_gc_wbarrier_value_copy", nullptr}, {"mono_gchandle_free", nullptr},
            {"mono_gchandle_get_target", nullptr}, {"mono_gchandle_is_in_domain", nullptr},
            {"mono_gchandle_new", nullptr}, {"mono_gchandle_new_weakref", nullptr}, {"mono_get_array_class", nullptr},
            {"mono_get_boolean_class", nullptr}, {"mono_get_byte_class", nullptr}, {"mono_get_char_class", nullptr},
            {"mono_get_config_dir", nullptr}, {"mono_get_corlib", nullptr}, {"mono_get_dbnull_object", nullptr},
            {"mono_get_delegate_begin_invoke", nullptr}, {"mono_get_delegate_end_invoke", nullptr},
            {"mono_get_delegate_invoke", nullptr}, {"mono_get_double_class", nullptr}, {"mono_get_enum_class", nullptr},
            {"mono_get_exception_appdomain_unloaded", nullptr}, {"mono_get_exception_argument", nullptr},
            {"mono_get_exception_argument_null", nullptr}, {"mono_get_exception_argument_out_of_range", nullptr},
            {"mono_get_exception_arithmetic", nullptr}, {"mono_get_exception_array_type_mismatch", nullptr},
            {"mono_get_exception_bad_image_format", nullptr}, {"mono_get_exception_bad_image_format2", nullptr},
            {"mono_get_exception_cannot_unload_appdomain", nullptr}, {"mono_get_exception_class", nullptr},
            {"mono_get_exception_divide_by_zero", nullptr}, {"mono_get_exception_execution_engine", nullptr},
            {"mono_get_exception_field_access", nullptr}, {"mono_get_exception_file_not_found", nullptr},
            {"mono_get_exception_file_not_found2", nullptr}, {"mono_get_exception_index_out_of_range", nullptr},
            {"mono_get_exception_invalid_cast", nullptr}, {"mono_get_exception_invalid_operation", nullptr},
            {"mono_get_exception_io", nullptr}, {"mono_get_exception_method_access", nullptr},
            {"mono_get_exception_missing_field", nullptr}, {"mono_get_exception_missing_method", nullptr},
            {"mono_get_exception_not_implemented", nullptr}, {"mono_get_exception_not_supported", nullptr},
            {"mono_get_exception_null_reference", nullptr}, {"mono_get_exception_out_of_memory", nullptr},
            {"mono_get_exception_overflow", nullptr}, {"mono_get_exception_reflection_type_load", nullptr},
            {"mono_get_exception_runtime_wrapped", nullptr}, {"mono_get_exception_security", nullptr},
            {"mono_get_exception_serialization", nullptr}, {"mono_get_exception_stack_overflow", nullptr},
            {"mono_get_exception_synchronization_lock", nullptr}, {"mono_get_exception_thread_abort", nullptr},
            {"mono_get_exception_thread_interrupted", nullptr}, {"mono_get_exception_thread_state", nullptr},
            {"mono_get_exception_type_initialization", nullptr}, {"mono_get_exception_type_load", nullptr},
            {"mono_get_find_plugin_callback", nullptr}, {"mono_get_inflated_method", nullptr},
            {"mono_get_int16_class", nullptr}, {"mono_get_int32_class", nullptr}, {"mono_get_int64_class", nullptr},
            {"mono_get_intptr_class", nullptr}, {"mono_get_machine_config", nullptr}, {"mono_get_method", nullptr},
            {"mono_get_method_constrained", nullptr}, {"mono_get_method_full", nullptr},
            {"mono_get_object_class", nullptr}, {"mono_get_root_domain", nullptr},
            {"mono_get_runtime_build_info", nullptr}, {"mono_get_sbyte_class", nullptr},
            {"mono_get_single_class", nullptr}, {"mono_get_string_class", nullptr}, {"mono_get_thread_class", nullptr},
            {"mono_get_uint16_class", nullptr}, {"mono_get_uint32_class", nullptr}, {"mono_get_uint64_class", nullptr},
            {"mono_get_uintptr_class", nullptr}, {"mono_get_void_class", nullptr}, {"mono_guid_to_string", nullptr},
            {"mono_guid_to_string_minimal", nullptr}, {"mono_hazard_pointer_get", nullptr},
            {"mono_image_add_to_name_cache", nullptr}, {"mono_image_addref", nullptr}, {"mono_image_close", nullptr},
            {"mono_image_ensure_section", nullptr}, {"mono_image_ensure_section_idx", nullptr},
            {"mono_image_fixup_vtable", nullptr}, {"mono_image_get_assembly", nullptr},
            {"mono_image_get_entry_point", nullptr}, {"mono_image_get_filename", nullptr},
            {"mono_image_get_guid", nullptr}, {"mono_image_get_name", nullptr}, {"mono_image_get_public_key", nullptr},
            {"mono_image_get_resource", nullptr}, {"mono_image_get_strong_name", nullptr},
            {"mono_image_get_table_info", nullptr}, {"mono_image_get_table_rows", nullptr},
            {"mono_image_has_authenticode_entry", nullptr}, {"mono_image_init", nullptr},
            {"mono_image_init_name_cache", nullptr}, {"mono_image_is_dynamic", nullptr},
            {"mono_image_load_file_for_image", nullptr}, {"mono_image_load_module", nullptr},
            {"mono_image_loaded", nullptr}, {"mono_image_loaded_by_guid", nullptr},
            {"mono_image_loaded_by_guid_full", nullptr}, {"mono_image_loaded_full", nullptr},
            {"mono_image_lookup_resource", nullptr}, {"mono_image_open", nullptr},
            {"mono_image_open_from_data", nullptr}, {"mono_image_open_from_data_full", nullptr},
            {"mono_image_open_from_data_with_name", nullptr}, {"mono_image_open_full", nullptr},
            {"mono_image_rva_map", nullptr}, {"mono_image_strerror", nullptr},
            {"mono_image_strong_name_position", nullptr}, {"mono_images_cleanup", nullptr},
            {"mono_images_init", nullptr}, {"mono_init", nullptr}, {"mono_init_from_assembly", nullptr},
            {"mono_init_version", nullptr}, {"mono_install_assembly_load_hook", nullptr},
            {"mono_install_assembly_postload_refonly_search_hook", nullptr},
            {"mono_install_assembly_postload_search_hook", nullptr}, {"mono_install_assembly_preload_hook", nullptr},
            {"mono_install_assembly_refonly_preload_hook", nullptr},
            {"mono_install_assembly_refonly_search_hook", nullptr}, {"mono_install_assembly_search_hook", nullptr},
            {"mono_install_ftnptr_eh_callback", nullptr}, {"mono_install_load_aot_data_hook", nullptr},
            {"mono_install_runtime_cleanup", nullptr}, {"mono_install_unhandled_exception_hook", nullptr},
            {"mono_internal_current_level", nullptr}, {"mono_internal_current_mask", nullptr},
            {"mono_is_debugger_attached", nullptr}, {"mono_jit_aot_compiling", nullptr}, {"mono_jit_cleanup", nullptr},
            {"mono_jit_exec", nullptr}, {"mono_jit_info_get_code_size", nullptr},
            {"mono_jit_info_get_code_start", nullptr}, {"mono_jit_info_get_method", nullptr},
            {"mono_jit_info_table_find", nullptr}, {"mono_jit_init", nullptr}, {"mono_jit_init_version", nullptr},
            {"mono_jit_parse_options", nullptr}, {"mono_jit_set_aot_mode", nullptr}, {"mono_jit_set_aot_only", nullptr},
            {"mono_jit_set_domain", nullptr}, {"mono_jit_set_trace_options", nullptr},
            {"mono_jit_thread_attach", nullptr}, {"mono_ldstr", nullptr}, {"mono_ldtoken", nullptr},
            {"mono_lls_find", nullptr}, {"mono_lls_get_hazardous_pointer_with_mask", nullptr},
            {"mono_lls_init", nullptr}, {"mono_lls_insert", nullptr}, {"mono_lls_remove", nullptr},
            {"mono_load_remote_field", nullptr}, {"mono_load_remote_field_new", nullptr},
            {"mono_loader_register_module", nullptr}, {"mono_lock_free_alloc", nullptr},
            {"mono_lock_free_allocator_check_consistency", nullptr},
            {"mono_lock_free_allocator_init_allocator", nullptr}, {"mono_lock_free_allocator_init_size_class", nullptr},
            {"mono_lock_free_free", nullptr}, {"mono_lock_free_queue_dequeue", nullptr},
            {"mono_lock_free_queue_enqueue", nullptr}, {"mono_lock_free_queue_init", nullptr},
            {"mono_lock_free_queue_node_init", nullptr}, {"mono_lock_free_queue_node_unpoison", nullptr},
            {"mono_locks_dump", nullptr}, {"mono_lookup_icall_symbol", nullptr}, {"mono_lookup_internal_call", nullptr},
            {"mono_lookup_pinvoke_call", nullptr}, {"mono_main", nullptr}, {"mono_marshal_string_to_utf16", nullptr},
            {"mono_md5_final", nullptr}, {"mono_md5_get_digest", nullptr}, {"mono_md5_get_digest_from_file", nullptr},
            {"mono_md5_init", nullptr}, {"mono_md5_update", nullptr}, {"mono_mem_account_register_counters", nullptr},
            {"mono_mem_account_type_name", nullptr}, {"mono_mempool_alloc", nullptr}, {"mono_mempool_alloc0", nullptr},
            {"mono_mempool_contains_addr", nullptr}, {"mono_mempool_destroy", nullptr},
            {"mono_mempool_foreach_block", nullptr}, {"mono_mempool_get_allocated", nullptr},
            {"mono_mempool_invalidate", nullptr}, {"mono_mempool_new", nullptr}, {"mono_mempool_new_size", nullptr},
            {"mono_mempool_stats", nullptr}, {"mono_mempool_strdup", nullptr}, {"mono_metadata_blob_heap", nullptr},
            {"mono_metadata_cleanup", nullptr}, {"mono_metadata_compute_size", nullptr},
            {"mono_metadata_custom_attrs_from_index", nullptr}, {"mono_metadata_declsec_from_index", nullptr},
            {"mono_metadata_decode_blob_size", nullptr}, {"mono_metadata_decode_row", nullptr},
            {"mono_metadata_decode_row_col", nullptr}, {"mono_metadata_decode_signed_value", nullptr},
            {"mono_metadata_decode_table_row", nullptr}, {"mono_metadata_decode_table_row_col", nullptr},
            {"mono_metadata_decode_value", nullptr}, {"mono_metadata_encode_value", nullptr},
            {"mono_metadata_events_from_typedef", nullptr}, {"mono_metadata_field_info", nullptr},
            {"mono_metadata_field_info_with_mempool", nullptr}, {"mono_metadata_free_array", nullptr},
            {"mono_metadata_free_inflated_signature", nullptr}, {"mono_metadata_free_marshal_spec", nullptr},
            {"mono_metadata_free_method_signature", nullptr}, {"mono_metadata_free_mh", nullptr},
            {"mono_metadata_free_type", nullptr}, {"mono_metadata_generic_class_foreach", nullptr},
            {"mono_metadata_generic_class_is_valuetype", nullptr}, {"mono_metadata_get_constant_index", nullptr},
            {"mono_metadata_get_generic_param_row", nullptr}, {"mono_metadata_get_inflated_signature", nullptr},
            {"mono_metadata_get_marshal_info", nullptr}, {"mono_metadata_guid_heap", nullptr},
            {"mono_metadata_implmap_from_method", nullptr}, {"mono_metadata_init", nullptr},
            {"mono_metadata_interfaces_from_typedef", nullptr},
            {"mono_metadata_load_generic_param_constraints_checked", nullptr},
            {"mono_metadata_load_generic_params", nullptr}, {"mono_metadata_locate", nullptr},
            {"mono_metadata_locate_token", nullptr}, {"mono_metadata_methods_from_event", nullptr},
            {"mono_metadata_methods_from_property", nullptr}, {"mono_metadata_nested_in_typedef", nullptr},
            {"mono_metadata_nesting_typedef", nullptr}, {"mono_metadata_packing_from_typedef", nullptr},
            {"mono_metadata_parse_array", nullptr}, {"mono_metadata_parse_custom_mod", nullptr},
            {"mono_metadata_parse_field_type", nullptr}, {"mono_metadata_parse_marshal_spec", nullptr},
            {"mono_metadata_parse_method_signature", nullptr}, {"mono_metadata_parse_method_signature_full", nullptr},
            {"mono_metadata_parse_mh", nullptr}, {"mono_metadata_parse_mh_full", nullptr},
            {"mono_metadata_parse_param", nullptr}, {"mono_metadata_parse_signature", nullptr},
            {"mono_metadata_parse_type", nullptr}, {"mono_metadata_parse_typedef_or_ref", nullptr},
            {"mono_metadata_properties_from_typedef", nullptr}, {"mono_metadata_signature_alloc", nullptr},
            {"mono_metadata_signature_dup", nullptr}, {"mono_metadata_signature_equal", nullptr},
            {"mono_metadata_string_heap", nullptr}, {"mono_metadata_token_from_dor", nullptr},
            {"mono_metadata_translate_token_index", nullptr}, {"mono_metadata_type_equal", nullptr},
            {"mono_metadata_type_hash", nullptr}, {"mono_metadata_typedef_from_field", nullptr},
            {"mono_metadata_typedef_from_method", nullptr}, {"mono_metadata_user_string", nullptr},
            {"mono_method_body_get_object", nullptr}, {"mono_method_can_access_field", nullptr},
            {"mono_method_can_access_method", nullptr}, {"mono_method_desc_free", nullptr},
            {"mono_method_desc_from_method", nullptr}, {"mono_method_desc_full_match", nullptr},
            {"mono_method_desc_is_full", nullptr}, {"mono_method_desc_match", nullptr},
            {"mono_method_desc_new", nullptr}, {"mono_method_desc_search_in_class", nullptr},
            {"mono_method_desc_search_in_image", nullptr}, {"mono_method_full_name", nullptr},
            {"mono_method_get_class", nullptr}, {"mono_method_get_context", nullptr},
            {"mono_method_get_flags", nullptr}, {"mono_method_get_generic_container", nullptr},
            {"mono_method_get_header", nullptr}, {"mono_method_get_header_checked", nullptr},
            {"mono_method_get_index", nullptr}, {"mono_method_get_last_managed", nullptr},
            {"mono_method_get_marshal_info", nullptr}, {"mono_method_get_name", nullptr},
            {"mono_method_get_object", nullptr}, {"mono_method_get_param_names", nullptr},
            {"mono_method_get_param_token", nullptr}, {"mono_method_get_reflection_name", nullptr},
            {"mono_method_get_signature", nullptr}, {"mono_method_get_signature_full", nullptr},
            {"mono_method_get_token", nullptr}, {"mono_method_get_unmanaged_thunk", nullptr},
            {"mono_method_has_marshal_info", nullptr}, {"mono_method_header_get_clauses", nullptr},
            {"mono_method_header_get_code", nullptr}, {"mono_method_header_get_locals", nullptr},
            {"mono_method_header_get_num_clauses", nullptr}, {"mono_method_print_code", nullptr},
            {"mono_method_signature", nullptr}, {"mono_method_signature_checked", nullptr},
            {"mono_method_verify", nullptr}, {"mono_mlist_alloc", nullptr}, {"mono_mlist_append", nullptr},
            {"mono_mlist_get_data", nullptr}, {"mono_mlist_last", nullptr}, {"mono_mlist_length", nullptr},
            {"mono_mlist_next", nullptr}, {"mono_mlist_prepend", nullptr}, {"mono_mlist_remove_item", nullptr},
            {"mono_mlist_set_data", nullptr}, {"mono_mlist_set_next", nullptr},
            {"mono_module_file_get_object", nullptr}, {"mono_module_get_object", nullptr},
            {"mono_monitor_enter", nullptr}, {"mono_monitor_enter_v4", nullptr}, {"mono_monitor_exit", nullptr},
            {"mono_monitor_try_enter", nullptr}, {"mono_mprotect", nullptr}, {"mono_native_getrootdir", nullptr},
            {"mono_native_thread_create", nullptr}, {"mono_native_thread_id_equals", nullptr},
            {"mono_native_thread_id_get", nullptr}, {"mono_native_thread_join", nullptr},
            {"mono_native_thread_set_name", nullptr}, {"mono_object_castclass_mbyref", nullptr},
            {"mono_object_clone", nullptr}, {"mono_object_describe", nullptr}, {"mono_object_describe_fields", nullptr},
            {"mono_object_get_class", nullptr}, {"mono_object_get_domain", nullptr}, {"mono_object_get_size", nullptr},
            {"mono_object_get_virtual_method", nullptr}, {"mono_object_get_vtable", nullptr},
            {"mono_object_hash", nullptr}, {"mono_object_is_alive", nullptr}, {"mono_object_isinst", nullptr},
            {"mono_object_isinst_mbyref", nullptr}, {"mono_object_new", nullptr},
            {"mono_object_new_alloc_specific", nullptr}, {"mono_object_new_fast", nullptr},
            {"mono_object_new_from_token", nullptr}, {"mono_object_new_specific", nullptr},
            {"mono_object_to_string", nullptr}, {"mono_object_unbox", nullptr}, {"mono_opcode_name", nullptr},
            {"mono_opcode_value", nullptr}, {"mono_opcodes", nullptr}, {"mono_pagesize", nullptr},
            {"mono_param_get_objects", nullptr}, {"mono_parse_default_optimizations", nullptr},
            {"mono_parse_env_options", nullptr}, {"mono_parse_options_from", nullptr},
            {"mono_path_canonicalize", nullptr}, {"mono_path_resolve_symlinks", nullptr},
            {"mono_pe_file_open", nullptr}, {"mono_perfcounter_foreach", nullptr}, {"mono_perfcounters_init", nullptr},
            {"mono_personality", nullptr}, {"mono_pmip", nullptr}, {"mono_poll", nullptr},
            {"mono_ppdb_get_signature", nullptr}, {"mono_print_method_from_ip", nullptr},
            {"mono_print_thread_dump", nullptr}, {"mono_print_thread_dump_from_ctx", nullptr},
            {"mono_print_unhandled_exception", nullptr}, {"mono_profiler_call_context_free_buffer", nullptr},
            {"mono_profiler_call_context_get_argument", nullptr}, {"mono_profiler_call_context_get_local", nullptr},
            {"mono_profiler_call_context_get_result", nullptr}, {"mono_profiler_call_context_get_this", nullptr},
            {"mono_profiler_create", nullptr}, {"mono_profiler_enable_allocations", nullptr},
            {"mono_profiler_enable_call_context_introspection", nullptr}, {"mono_profiler_enable_coverage", nullptr},
            {"mono_profiler_enable_fileio", nullptr}, {"mono_profiler_enable_sampling", nullptr},
            {"mono_profiler_get_all_coverage_data", nullptr}, {"mono_profiler_get_coverage_data", nullptr},
            {"mono_profiler_get_sample_mode", nullptr}, {"mono_profiler_init_etw", nullptr},
            {"mono_profiler_install", nullptr}, {"mono_profiler_install_allocation", nullptr},
            {"mono_profiler_install_enter_leave", nullptr}, {"mono_profiler_install_exception", nullptr},
            {"mono_profiler_install_fileio", nullptr}, {"mono_profiler_install_gc", nullptr},
            {"mono_profiler_install_jit_end", nullptr}, {"mono_profiler_install_thread", nullptr},
            {"mono_profiler_load", nullptr}, {"mono_profiler_reset_all_coverage", nullptr},
            {"mono_profiler_reset_coverage", nullptr}, {"mono_profiler_set_assembly_loaded_callback", nullptr},
            {"mono_profiler_set_assembly_loading_callback", nullptr},
            {"mono_profiler_set_assembly_unloaded_callback", nullptr},
            {"mono_profiler_set_assembly_unloading_callback", nullptr},
            {"mono_profiler_set_call_instrumentation_filter_callback", nullptr},
            {"mono_profiler_set_class_failed_callback", nullptr}, {"mono_profiler_set_class_loaded_callback", nullptr},
            {"mono_profiler_set_class_loading_callback", nullptr}, {"mono_profiler_set_cleanup_callback", nullptr},
            {"mono_profiler_set_context_loaded_callback", nullptr},
            {"mono_profiler_set_context_unloaded_callback", nullptr},
            {"mono_profiler_set_coverage_filter_callback", nullptr},
            {"mono_profiler_set_domain_loaded_callback", nullptr},
            {"mono_profiler_set_domain_loading_callback", nullptr}, {"mono_profiler_set_domain_name_callback", nullptr},
            {"mono_profiler_set_domain_unloaded_callback", nullptr},
            {"mono_profiler_set_domain_unloading_callback", nullptr}, {"mono_profiler_set_events", nullptr},
            {"mono_profiler_set_exception_clause_callback", nullptr},
            {"mono_profiler_set_exception_throw_callback", nullptr}, {"mono_profiler_set_fileio_callback", nullptr},
            {"mono_profiler_set_gc_allocation_callback", nullptr}, {"mono_profiler_set_gc_event_callback", nullptr},
            {"mono_profiler_set_gc_finalized_callback", nullptr},
            {"mono_profiler_set_gc_finalized_object_callback", nullptr},
            {"mono_profiler_set_gc_finalizing_callback", nullptr},
            {"mono_profiler_set_gc_finalizing_object_callback", nullptr},
            {"mono_profiler_set_gc_handle_created_callback", nullptr},
            {"mono_profiler_set_gc_handle_deleted_callback", nullptr}, {"mono_profiler_set_gc_moves_callback", nullptr},
            {"mono_profiler_set_gc_resize_callback", nullptr}, {"mono_profiler_set_gc_root_register_callback", nullptr},
            {"mono_profiler_set_gc_root_unregister_callback", nullptr},
            {"mono_profiler_set_gc_roots_callback", nullptr}, {"mono_profiler_set_image_failed_callback", nullptr},
            {"mono_profiler_set_image_loaded_callback", nullptr}, {"mono_profiler_set_image_loading_callback", nullptr},
            {"mono_profiler_set_image_unloaded_callback", nullptr},
            {"mono_profiler_set_image_unloading_callback", nullptr},
            {"mono_profiler_set_iomap_report_callback", nullptr}, {"mono_profiler_set_jit_begin_callback", nullptr},
            {"mono_profiler_set_jit_chunk_created_callback", nullptr},
            {"mono_profiler_set_jit_chunk_destroyed_callback", nullptr},
            {"mono_profiler_set_jit_code_buffer_callback", nullptr}, {"mono_profiler_set_jit_done_callback", nullptr},
            {"mono_profiler_set_jit_failed_callback", nullptr},
            {"mono_profiler_set_method_begin_invoke_callback", nullptr},
            {"mono_profiler_set_method_end_invoke_callback", nullptr},
            {"mono_profiler_set_method_enter_callback", nullptr},
            {"mono_profiler_set_method_exception_leave_callback", nullptr},
            {"mono_profiler_set_method_free_callback", nullptr}, {"mono_profiler_set_method_leave_callback", nullptr},
            {"mono_profiler_set_method_tail_call_callback", nullptr},
            {"mono_profiler_set_monitor_acquired_callback", nullptr},
            {"mono_profiler_set_monitor_contention_callback", nullptr},
            {"mono_profiler_set_monitor_failed_callback", nullptr},
            {"mono_profiler_set_runtime_initialized_callback", nullptr},
            {"mono_profiler_set_runtime_shutdown_begin_callback", nullptr},
            {"mono_profiler_set_runtime_shutdown_end_callback", nullptr},
            {"mono_profiler_set_sample_hit_callback", nullptr}, {"mono_profiler_set_sample_mode", nullptr},
            {"mono_profiler_set_thread_exited_callback", nullptr}, {"mono_profiler_set_thread_name_callback", nullptr},
            {"mono_profiler_set_thread_started_callback", nullptr},
            {"mono_profiler_set_thread_stopped_callback", nullptr},
            {"mono_profiler_set_thread_stopping_callback", nullptr},
            {"mono_profiler_set_vtable_failed_callback", nullptr},
            {"mono_profiler_set_vtable_loaded_callback", nullptr},
            {"mono_profiler_set_vtable_loading_callback", nullptr}, {"mono_property_get_flags", nullptr},
            {"mono_property_get_get_method", nullptr}, {"mono_property_get_name", nullptr},
            {"mono_property_get_object", nullptr}, {"mono_property_get_parent", nullptr},
            {"mono_property_get_set_method", nullptr}, {"mono_property_get_value", nullptr},
            {"mono_property_hash_destroy", nullptr}, {"mono_property_hash_insert", nullptr},
            {"mono_property_hash_lookup", nullptr}, {"mono_property_hash_new", nullptr},
            {"mono_property_hash_remove_object", nullptr}, {"mono_property_set_value", nullptr},
            {"mono_ptr_class_get", nullptr}, {"mono_raise_exception", nullptr},
            {"mono_reflection_assembly_get_assembly", nullptr}, {"mono_reflection_free_type_info", nullptr},
            {"mono_reflection_get_custom_attrs", nullptr}, {"mono_reflection_get_custom_attrs_blob", nullptr},
            {"mono_reflection_get_custom_attrs_by_type", nullptr}, {"mono_reflection_get_custom_attrs_data", nullptr},
            {"mono_reflection_get_custom_attrs_info", nullptr}, {"mono_reflection_get_token", nullptr},
            {"mono_reflection_get_type", nullptr}, {"mono_reflection_parse_type", nullptr},
            {"mono_reflection_type_from_name", nullptr}, {"mono_reflection_type_get_type", nullptr},
            {"mono_register_bundled_assemblies", nullptr}, {"mono_register_config_for_assembly", nullptr},
            {"mono_register_machine_config", nullptr}, {"mono_register_symfile_for_assembly", nullptr},
            {"mono_reraise_exception", nullptr}, {"mono_runtime_class_init", nullptr},
            {"mono_runtime_cleanup", nullptr}, {"mono_runtime_delegate_invoke", nullptr},
            {"mono_runtime_exec_main", nullptr}, {"mono_runtime_exec_managed_code", nullptr},
            {"mono_runtime_get_main_args", nullptr}, {"mono_runtime_init", nullptr}, {"mono_runtime_invoke", nullptr},
            {"mono_runtime_invoke_array", nullptr}, {"mono_runtime_is_shutting_down", nullptr},
            {"mono_runtime_object_init", nullptr}, {"mono_runtime_quit", nullptr},
            {"mono_runtime_resource_check_limit", nullptr}, {"mono_runtime_resource_limit", nullptr},
            {"mono_runtime_resource_set_callback", nullptr}, {"mono_runtime_run_main", nullptr},
            {"mono_runtime_set_main_args", nullptr}, {"mono_runtime_set_shutting_down", nullptr},
            {"mono_runtime_unhandled_exception_policy_set", nullptr}, {"mono_security_core_clr_get_options", nullptr},
            {"mono_security_core_clr_require_elevated_permissions", nullptr},
            {"mono_security_core_clr_set_options", nullptr}, {"mono_security_enable_core_clr", nullptr},
            {"mono_security_set_core_clr_platform_callback", nullptr}, {"mono_security_set_mode", nullptr},
            {"mono_set_allocator_vtable", nullptr}, {"mono_set_assemblies_path", nullptr},
            {"mono_set_assemblies_path_null_separated", nullptr}, {"mono_set_break_policy", nullptr},
            {"mono_set_config_dir", nullptr}, {"mono_set_crash_chaining", nullptr}, {"mono_set_defaults", nullptr},
            {"mono_set_dirs", nullptr}, {"mono_set_find_plugin_callback", nullptr},
            {"mono_set_ignore_version_and_key_when_finding_assemblies_already_loaded", nullptr},
            {"mono_set_is_debugger_attached", nullptr}, {"mono_set_rootdir", nullptr},
            {"mono_set_signal_chaining", nullptr}, {"mono_sha1_final", nullptr}, {"mono_sha1_get_digest", nullptr},
            {"mono_sha1_get_digest_from_file", nullptr}, {"mono_sha1_init", nullptr}, {"mono_sha1_update", nullptr},
            {"mono_shared_area", nullptr}, {"mono_shared_area_for_pid", nullptr},
            {"mono_shared_area_instances", nullptr}, {"mono_shared_area_remove", nullptr},
            {"mono_shared_area_unload", nullptr}, {"mono_signature_explicit_this", nullptr},
            {"mono_signature_full_name", nullptr}, {"mono_signature_get_call_conv", nullptr},
            {"mono_signature_get_desc", nullptr}, {"mono_signature_get_param_count", nullptr},
            {"mono_signature_get_params", nullptr}, {"mono_signature_get_return_type", nullptr},
            {"mono_signature_hash", nullptr}, {"mono_signature_is_instance", nullptr},
            {"mono_signature_param_is_out", nullptr}, {"mono_signature_vararg_start", nullptr},
            {"mono_signbit_double", nullptr}, {"mono_signbit_float", nullptr}, {"mono_stack_walk", nullptr},
            {"mono_stack_walk_async_safe", nullptr}, {"mono_stack_walk_no_il", nullptr},
            {"mono_store_remote_field", nullptr}, {"mono_store_remote_field_new", nullptr},
            {"mono_string_chars", nullptr}, {"mono_string_empty", nullptr}, {"mono_string_empty_wrapper", nullptr},
            {"mono_string_equal", nullptr}, {"mono_string_from_bstr", nullptr}, {"mono_string_from_utf16", nullptr},
            {"mono_string_from_utf32", nullptr}, {"mono_string_hash", nullptr}, {"mono_string_intern", nullptr},
            {"mono_string_is_interned", nullptr}, {"mono_string_length", nullptr}, {"mono_string_new", nullptr},
            {"mono_string_new_len", nullptr}, {"mono_string_new_size", nullptr}, {"mono_string_new_utf16", nullptr},
            {"mono_string_new_utf32", nullptr}, {"mono_string_new_wrapper", nullptr}, {"mono_string_to_utf16", nullptr},
            {"mono_string_to_utf32", nullptr}, {"mono_string_to_utf8", nullptr},
            {"mono_string_to_utf8_checked", nullptr}, {"mono_stringify_assembly_name", nullptr},
            {"mono_table_info_get_rows", nullptr}, {"mono_thread_attach", nullptr}, {"mono_thread_cleanup", nullptr},
            {"mono_thread_create", nullptr}, {"mono_thread_current", nullptr}, {"mono_thread_detach", nullptr},
            {"mono_thread_detach_if_exiting", nullptr}, {"mono_thread_exit", nullptr},
            {"mono_thread_get_main", nullptr}, {"mono_thread_get_managed_id", nullptr},
            {"mono_thread_get_name_utf8", nullptr}, {"mono_thread_get_undeniable_exception", nullptr},
            {"mono_thread_hazardous_queue_free", nullptr}, {"mono_thread_hazardous_try_free", nullptr},
            {"mono_thread_hazardous_try_free_all", nullptr}, {"mono_thread_info_detach", nullptr},
            {"mono_thread_info_get_small_id", nullptr}, {"mono_thread_info_register_small_id", nullptr},
            {"mono_thread_info_yield", nullptr}, {"mono_thread_init", nullptr}, {"mono_thread_is_foreign", nullptr},
            {"mono_thread_manage", nullptr}, {"mono_thread_new_init", nullptr}, {"mono_thread_pool_cleanup", nullptr},
            {"mono_thread_pop_appdomain_ref", nullptr}, {"mono_thread_push_appdomain_ref", nullptr},
            {"mono_thread_set_main", nullptr}, {"mono_thread_set_manage_callback", nullptr},
            {"mono_thread_stop", nullptr}, {"mono_thread_suspend_all_other_threads", nullptr},
            {"mono_threads_assert_gc_safe_region", nullptr}, {"mono_threads_assert_gc_unsafe_region", nullptr},
            {"mono_threads_attach_coop", nullptr}, {"mono_threads_attach_tools_thread", nullptr},
            {"mono_threads_detach_coop", nullptr}, {"mono_threads_enter_gc_safe_region", nullptr},
            {"mono_threads_enter_gc_safe_region_unbalanced", nullptr}, {"mono_threads_enter_gc_unsafe_region", nullptr},
            {"mono_threads_enter_gc_unsafe_region_unbalanced", nullptr}, {"mono_threads_exit_gc_safe_region", nullptr},
            {"mono_threads_exit_gc_safe_region_unbalanced", nullptr}, {"mono_threads_exit_gc_unsafe_region", nullptr},
            {"mono_threads_exit_gc_unsafe_region_unbalanced", nullptr}, {"mono_threads_get_default_stacksize", nullptr},
            {"mono_threads_request_thread_dump", nullptr}, {"mono_threads_set_default_stacksize", nullptr},
            {"mono_threads_set_shutting_down", nullptr}, {"mono_trace_init", nullptr},
            {"mono_trace_set_level_string", nullptr}, {"mono_trace_set_log_handler", nullptr},
            {"mono_trace_set_mask_string", nullptr}, {"mono_trace_set_print_handler", nullptr},
            {"mono_trace_set_printerr_handler", nullptr}, {"mono_tracev_inner", nullptr},
            {"mono_type_create_from_typespec", nullptr}, {"mono_type_full_name", nullptr},
            {"mono_type_generic_inst_is_valuetype", nullptr}, {"mono_type_get_array_type", nullptr},
            {"mono_type_get_attrs", nullptr}, {"mono_type_get_class", nullptr}, {"mono_type_get_desc", nullptr},
            {"mono_type_get_modifiers", nullptr}, {"mono_type_get_name", nullptr}, {"mono_type_get_name_full", nullptr},
            {"mono_type_get_object", nullptr}, {"mono_type_get_ptr_type", nullptr},
            {"mono_type_get_signature", nullptr}, {"mono_type_get_type", nullptr},
            {"mono_type_get_underlying_type", nullptr}, {"mono_type_is_byref", nullptr},
            {"mono_type_is_pointer", nullptr}, {"mono_type_is_primitive", nullptr}, {"mono_type_is_reference", nullptr},
            {"mono_type_is_struct", nullptr}, {"mono_type_is_valid_enum_basetype", nullptr},
            {"mono_type_is_void", nullptr}, {"mono_type_size", nullptr}, {"mono_type_stack_size", nullptr},
            {"mono_type_to_unmanaged", nullptr}, {"mono_unhandled_exception", nullptr},
            {"mono_unicode_from_external", nullptr}, {"mono_unicode_to_external", nullptr},
            {"mono_unity_alloc", nullptr}, {"mono_unity_allocation_granularity", nullptr},
            {"mono_unity_array_new_2d", nullptr}, {"mono_unity_array_new_3d", nullptr},
            {"mono_unity_array_object_header_size", nullptr}, {"mono_unity_assembly_mempool_chunk_foreach", nullptr},
            {"mono_unity_backtrace_from_context", nullptr}, {"mono_unity_capture_memory_snapshot", nullptr},
            {"mono_unity_class_field_is_literal", nullptr}, {"mono_unity_class_for_each", nullptr},
            {"mono_unity_class_get", nullptr}, {"mono_unity_class_get_data_size", nullptr},
            {"mono_unity_class_get_generic_argument_at", nullptr},
            {"mono_unity_class_get_generic_argument_count", nullptr},
            {"mono_unity_class_get_generic_parameter_at", nullptr},
            {"mono_unity_class_get_generic_parameter_count", nullptr},
            {"mono_unity_class_get_generic_type_definition", nullptr}, {"mono_unity_class_is_abstract", nullptr},
            {"mono_unity_class_is_interface", nullptr}, {"mono_unity_class_is_open_constructed_type", nullptr},
            {"mono_unity_class_try_get_vtable", nullptr}, {"mono_unity_domain_mempool_chunk_foreach", nullptr},
            {"mono_unity_domain_set_config", nullptr}, {"mono_unity_domain_unload", nullptr},
            {"mono_unity_error_convert_to_exception", nullptr}, {"mono_unity_free_captured_memory_snapshot", nullptr},
            {"mono_unity_g_free", nullptr}, {"mono_unity_gc_disable", nullptr}, {"mono_unity_gc_enable", nullptr},
            {"mono_unity_gc_handles_foreach_get_target", nullptr}, {"mono_unity_gc_heap_foreach", nullptr},
            {"mono_unity_gc_is_disabled", nullptr}, {"mono_unity_gc_set_mode", nullptr},
            {"mono_unity_get_data_dir", nullptr}, {"mono_unity_get_unitytls_interface", nullptr},
            {"mono_unity_heap_validation", nullptr}, {"mono_unity_image_set_mempool_chunk_foreach", nullptr},
            {"mono_unity_install_memory_callbacks", nullptr}, {"mono_unity_install_unitytls_interface", nullptr},
            {"mono_unity_jit_cleanup", nullptr}, {"mono_unity_liveness_allocate_struct", nullptr},
            {"mono_unity_liveness_calculation_begin", nullptr}, {"mono_unity_liveness_calculation_end", nullptr},
            {"mono_unity_liveness_calculation_from_root", nullptr},
            {"mono_unity_liveness_calculation_from_statics", nullptr}, {"mono_unity_liveness_finalize", nullptr},
            {"mono_unity_liveness_free_struct", nullptr}, {"mono_unity_liveness_start_gc_world", nullptr},
            {"mono_unity_liveness_stop_gc_world", nullptr},
            {"mono_unity_loader_get_last_error_and_error_prepare_exception", nullptr},
            {"mono_unity_lock_dynamic_function_access_tables64", nullptr}, {"mono_unity_managed_callstack", nullptr},
            {"mono_unity_method_get_token", nullptr}, {"mono_unity_object_header_size", nullptr},
            {"mono_unity_offset_of_array_bounds_in_array_object_header", nullptr},
            {"mono_unity_offset_of_array_length_in_array_object_header", nullptr},
            {"mono_unity_oop_get_dynamic_function_access_table64", nullptr},
            {"mono_unity_oop_get_stack_frame_details", nullptr}, {"mono_unity_oop_init", nullptr},
            {"mono_unity_oop_iterate_dynamic_function_access_tables64", nullptr}, {"mono_unity_oop_shutdown", nullptr},
            {"mono_unity_register_path_remapper", nullptr}, {"mono_unity_root_domain_mempool_chunk_foreach", nullptr},
            {"mono_unity_runtime_set_main_args", nullptr}, {"mono_unity_set_data_dir", nullptr},
            {"mono_unity_set_editor_logging_callback", nullptr}, {"mono_unity_set_embeddinghostname", nullptr},
            {"mono_unity_set_enable_handler_block_guards", nullptr}, {"mono_unity_set_vprintf_func", nullptr},
            {"mono_unity_socket_security_enabled_set", nullptr}, {"mono_unity_start_gc_world", nullptr},
            {"mono_unity_stop_gc_world", nullptr}, {"mono_unity_string_empty_wrapper", nullptr},
            {"mono_unity_thread_fast_attach", nullptr}, {"mono_unity_thread_fast_detach", nullptr},
            {"mono_unity_type_get_name_full_chunked", nullptr}, {"mono_unity_type_is_pointer_type", nullptr},
            {"mono_unity_type_is_static", nullptr}, {"mono_unity_unlock_dynamic_function_access_tables64", nullptr},
            {"mono_unity_vtable_get_static_field_data", nullptr}, {"mono_upgrade_remote_class_wrapper", nullptr},
            {"mono_use_interpreter", nullptr}, {"mono_use_llvm", nullptr}, {"mono_utf8_from_external", nullptr},
            {"mono_utf8_validate_and_len", nullptr}, {"mono_utf8_validate_and_len_with_bounds", nullptr},
            {"mono_validate_object_pointer", nullptr}, {"mono_validate_string_pointer", nullptr},
            {"mono_valloc", nullptr}, {"mono_valloc_aligned", nullptr}, {"mono_valloc_granule", nullptr},
            {"mono_value_box", nullptr}, {"mono_value_copy", nullptr}, {"mono_value_copy_array", nullptr},
            {"mono_value_describe_fields", nullptr}, {"mono_verifier_set_mode", nullptr},
            {"mono_verify_corlib", nullptr}, {"mono_vfree", nullptr}, {"mono_vtable_class", nullptr},
            {"mono_vtable_domain", nullptr}, {"mono_vtable_get_static_field_data", nullptr},
            {"mono_win32_compat_CopyMemory", nullptr}, {"mono_win32_compat_FillMemory", nullptr},
            {"mono_win32_compat_MoveMemory", nullptr}, {"mono_win32_compat_ZeroMemory", nullptr},
            {"unity_mono_method_is_generic", nullptr}, {"unity_mono_method_is_inflated", nullptr},
            {"unity_mono_reflection_method_get_method", nullptr}
        };
    };

    class Il2cpp {
    public:
        struct Domain;
        struct Assembly;
        struct Type;
        struct Table;
        struct Image;
        struct Class;
        struct Field;
        struct Method;

    public:
        static auto SetModule(const HMODULE hModule) -> void {
            std::ofstream(stdout) << \
                R"(      ___           ___                       ___           ___                    ___           ___           ___           ___     )" << "\n" << \
                R"(     /\__\         /\__\          ___        /\  \         |\__\                  /\__\         /\  \         /\  \         /\__\    )" << "\n" << \
                R"(    /:/  /        /::|  |        /\  \       \:\  \        |:|  |                /:/  /        /::\  \       /::\  \       /:/  /    )" << "\n" << \
                R"(   /:/  /        /:|:|  |        \:\  \       \:\  \       |:|  |               /:/__/        /:/\:\  \     /:/\:\  \     /:/__/     )" << "\n" << \
                R"(  /:/  /  ___   /:/|:|  |__      /::\__\      /::\  \      |:|__|__            /::\  \ ___   /::\~\:\  \   /:/  \:\  \   /::\__\____ )" << "\n" << \
                R"( /:/__/  /\__\ /:/ |:| /\__\  __/:/\/__/     /:/\:\__\     /::::\__\          /:/\:\  /\__\ /:/\:\ \:\__\ /:/__/ \:\__\ /:/\:::::\__\)" << "\n" << \
                R"( \:\  \ /:/  / \/__|:|/:/  / /\/:/  /       /:/  \/__/    /:/~~/~             \/__\:\/:/  / \/__\:\/:/  / \:\  \  \/__/ \/_|:|~~|~   )" << "\n" << \
                R"(  \:\  /:/  /      |:/:/  /  \::/__/       /:/  /        /:/  /                    \::/  /       \::/  /   \:\  \          |:|  |    )" << "\n" << \
                R"(   \:\/:/  /       |::/  /    \:\__\       \/__/         \/__/                     /:/  /        /:/  /     \:\  \         |:|  |    )" << "\n" << \
                R"(    \::/  /        /:/  /      \/__/                                              /:/  /        /:/  /       \:\__\        |:|  |    )" << "\n" << \
                R"(     \/__/         \/__/                                                          \/__/         \/__/         \/__/         \|__|    )" << "\n" << \
                R"(                                                                                                                                     )" << "\n" << \
                R"(=====================================================================================================================================)" << "\n" << \
                R"(Unity Hack Library By 遂沫 2023/8/25 Mode: IL2CPP)" << "\n" << std::endl;

            hModule_ = hModule;
            size_t errorNum = 0, i = 0, max_ = address_.size();
            for (auto& [name, address] : address_) {
                address = static_cast<void*>(GetProcAddress(hModule, name.c_str()));
                if (!address) {
                    errorNum++;
                    continue;
                }
                LOG_DEBUG(std::format("[[{:04d}|{:04d}]] 获取API \"{}\" 地址: {:#010X}\r", ++i, max_, name, reinterpret_cast<std::uintptr_t>(address)));
            }
            if (errorNum != 0)
                LOG_WARNING(std::format("\n无法获取API数量：{} \n", errorNum));

            LOG_DEBUG("il2cpp_thread_attach...\n");
            static_cast<Domain* (*)(Domain * domain)>(address_["il2cpp_thread_attach"])(Domain::GetRoot());
            CSharper::SetIL2cppMod();
            LOG_DEBUG("获取Unity函数...\n");
            CSharper::SetMap(address_);
            LOG_DEBUG("IL2CPP运行时加载完成!\n");
        }

        static auto Dump(const std::string& file) -> void {
            std::ofstream io(file + "\\dump.cs", std::fstream::out);

            io << \
                "/*" << "\n" << \
                R"(*      ___           ___                       ___           ___                    ___           ___           ___           ___     )" << "\n" << \
                R"(*     /\__\         /\__\          ___        /\  \         |\__\                  /\__\         /\  \         /\  \         /\__\    )" << "\n" << \
                R"(*    /:/  /        /::|  |        /\  \       \:\  \        |:|  |                /:/  /        /::\  \       /::\  \       /:/  /    )" << "\n" << \
                R"(*   /:/  /        /:|:|  |        \:\  \       \:\  \       |:|  |               /:/__/        /:/\:\  \     /:/\:\  \     /:/__/     )" << "\n" << \
                R"(*  /:/  /  ___   /:/|:|  |__      /::\__\      /::\  \      |:|__|__            /::\  \ ___   /::\~\:\  \   /:/  \:\  \   /::\__\____ )" << "\n" << \
                R"(* /:/__/  /\__\ /:/ |:| /\__\  __/:/\/__/     /:/\:\__\     /::::\__\          /:/\:\  /\__\ /:/\:\ \:\__\ /:/__/ \:\__\ /:/\:::::\__\)" << "\n" << \
                R"(* \:\  \ /:/  / \/__|:|/:/  / /\/:/  /       /:/  \/__/    /:/~~/~             \/__\:\/:/  / \/__\:\/:/  / \:\  \  \/__/ \/_|:|~~|~   )" << "\n" << \
                R"(*  \:\  /:/  /      |:/:/  /  \::/__/       /:/  /        /:/  /                    \::/  /       \::/  /   \:\  \          |:|  |    )" << "\n" << \
                R"(*   \:\/:/  /       |::/  /    \:\__\       \/__/         \/__/                     /:/  /        /:/  /     \:\  \         |:|  |    )" << "\n" << \
                R"(*    \::/  /        /:/  /      \/__/                                              /:/  /        /:/  /       \:\__\        |:|  |    )" << "\n" << \
                R"(*     \/__/         \/__/                                                          \/__/         \/__/         \/__/         \|__|    )" << "\n" << \
                R"(*                                                                                                                                     )" << "\n" << \
                R"(*=====================================================================================================================================)" << "\n" << \
                R"(*Unity Hack Library By 遂沫 2023/8/25 Mode: IL2CPP)" << "\n*/" << std::endl;

            size_t image_s{}, image_i{};
            std::list<Assembly*> assemblys;
            Assembly::EnumAssemblys(assemblys);
            image_s = assemblys.size();
            for (const auto& assembly : assemblys) {
                if (!assembly)
                    continue;

                Image* image_{};
                try {
                    image_ = assembly->GetImage();
                } catch (...) {
                    continue;
                }

                if (image_ == nullptr) {
                    continue;
                }

                int class_s{0}, class_i{0};
                try {
                    class_s = image_->GetClassCount();
                } catch (...) {
                    continue;
                }

                std::string image_name{};
                try {
                    image_name = image_->GetName();
                } catch (...) {
                    continue;
                }

                std::list<Class*> classes_;
                try {
                    image_->EnumClasses(classes_);
                } catch (...) {
                    continue;
                }

                for (auto& klass : classes_) {
                    if (klass == 0)
                        continue;

                    io << std::format("[{:04d}|{:04d}] {} \n", ++image_i, image_s, image_name);
                    io << std::format("using namespace {};\n", klass->GetNamespace());
                    io << std::format("[{:04d}|{:04d}] class {} {}\n", ++class_i, class_s, klass->GetName(), klass->GetParent() ? ": " + klass->GetParent()->GetName() : "");
                    io << "{\n";

                    int field_i{0}, method_i{0};
                    std::list<Field*> fields_;
                    klass->EnumFields(fields_);
                    std::list<Method*> methods_;
                    klass->EnumMethods(methods_);

                    io << std::format("    // 变量 -count:{}\n", fields_.size());
                    for (auto& field : fields_) {
                        if (!field)
                            continue;
                        io << std::format("    [{:04d}|{:04d}] |Offset: {:+#06X}| {} {} {};\n", ++field_i, fields_.size(), field->GetOffset(), field->IsStatic() ? "static" : "      ", field->GetType()->GetName(), field->GetName());
                    }

                    io << std::format("\n    // 函数 -count:{}\n", methods_.size());
                    for (auto& method : methods_) {
                        if (!method)
                            continue;
                        io << std::format("    [Flags: {:032b}] [ParamCount: {:04d}]\n    [{:04d}|{:04d}] |RVA: {:+#010X}| {} {} {}(",
                            method->GetFlags(), method->GetParamCount(), ++method_i, methods_.size(), method->GetAddress() - reinterpret_cast<std::uintptr_t>(hModule_),
                            method->IsStatic() ? "static" : "      ", method->GetRetType()->GetName(), method->GetName());

                        std::map<std::string, Type*> map_;
                        method->EnumParam(map_);
                        for (auto& [name, type] : map_) {
                            if (!type)
                                continue;
                            io << std::format("{} {}, ", type->GetName(), name);
                        }

                        if (map_.size() > 0) {
                            io.seekp(-1, std::ios_base::end);
                            io << "";
                            io.seekp(-1, std::ios_base::end);
                            io << "";
                        }

                        io << ");\n\n";
                    }

                    io << "} // Dump Tool By 遂沫 2023 \n";
                }
            }
            io.close();
            SetFileAttributesA((file + "\\dump.cs").c_str(), FILE_ATTRIBUTE_READONLY);
            SetFileAttributesA((file + "\\dump.cs").c_str(), FILE_ATTRIBUTE_SYSTEM);
        }

        struct Domain {
        public:
            static auto GetRoot() -> Domain* {
                try {
                    return static_cast<Domain * (*)()>(address_["il2cpp_domain_get"])();
                } catch (...) {
                    return nullptr;
                }
            }
        };

        struct Assembly {
        private:
            Image* image;
            uint32_t token;
            int32_t  referencedAssemblyStart;
            int32_t  referencedAssemblyCount;

            struct {
                const char* name;
                const char* culture;
                const char* hash_value;
                const char* public_key;
                uint32_t    hash_alg;
                int32_t     hash_len;
                uint32_t    flags;
                int32_t     major;
                int32_t     minor;
                int32_t     build;
                int32_t     revision;
                uint8_t     public_key_token[8];
            }               aname{};

        public:
            Assembly() = delete;

            static auto EnumAssemblys(std::list<Assembly*>& assembly) -> size_t {
                try {
                    size_t     nrofassemblies = 0;
                    const auto assemblies = static_cast<Assembly * *(*)(const Domain * domain, size_t * size)>(address_["il2cpp_domain_get_assemblies"])(Domain::GetRoot(), &nrofassemblies);
                    for (auto i = 0; i < nrofassemblies; i++)
                        assembly.push_back(assemblies[i]);
                    return assembly.size();
                } catch (...) {
                    return assembly.size();
                }
            }

            auto GetImage() const -> Image* {
                try {
                    return static_cast<Image * (*)(const Assembly * type)>(address_["il2cpp_assembly_get_image"])(this);
                } catch (...) {
                    return nullptr;
                }
            }

            auto GetName() const -> std::string {
                try {
                    return static_cast<const char* (*)(const Assembly * type)>(address_["il2cpp_class_get_assemblyname"])(this);
                } catch (...) {}
            }
        };

        struct Type {
        public:
            Type() = delete;

            auto GetName() -> std::string {
                try {
                    return static_cast<const char* (*)(Type * type)>(address_["il2cpp_type_get_name"])(this);
                } catch (...) {
                    return "";
                }
            }
        };

        struct Image {
        private:
            const char* name;
            const char* nameNoExt;
            Assembly* assembly;

            int32_t  typeStart;
            uint32_t typeCount;

            int32_t  exportedTypeStart;
            uint32_t exportedTypeCount;

            int32_t  customAttributeStart;
            uint32_t customAttributeCount;

            int32_t entryPointIndex;
        public:
            Image() = delete;

            auto GetName() -> std::string {
                try {
                    return static_cast<const char* (*)(Image * _this)>(address_["il2cpp_image_get_name"])(this);
                } catch (...) {
                    return "";
                }
            }

            auto GetFile() -> std::string {
                try {
                    return static_cast<const char* (*)(Image * _this)>(address_["il2cpp_image_get_filename"])(this);
                } catch (...) {
                    return "";
                }
            }

            auto EnumClasses(std::list<Class*>& classes) const -> size_t {
                try {
                    const auto count = static_cast<size_t(*)(const Image * _this)>(address_["il2cpp_image_get_class_count"])(this);
                    for (size_t i = 0; i < count; i++) {
                        if (auto klass = static_cast<Class * (*)(const Image * _this, size_t index)>(address_["il2cpp_image_get_class"])(this, i))
                            classes.push_back(klass);
                    }
                    return classes.size();
                } catch (...) {
                    return classes.size();
                }
            }

            auto GetClassCount() const -> size_t {
                try {
                    return static_cast<size_t(*)(const Image * _this)>(address_["il2cpp_image_get_class_count"])(this);;
                } catch (...) {
                    return 0;
                }
            }

            auto GetClassFromName(const std::string& name, const std::string& name_space = "") const -> Class* {
                std::list<Class*> classes;
                this->EnumClasses(classes);
                for (const auto& klass : classes) {
                    if (klass == nullptr)
                        continue;
                    if (klass->GetName() != name)
                        continue;
                    if (!name_space.empty())
                        if (klass->GetNamespace() != name_space)
                            continue;
                    return klass;
                }
                return nullptr;
            }
        };

        struct Class {
        private:
            // The following fields are always valid for a Il2CppClass structure
            Image* image;
            void* gc_desc;
            const char* name;
            const char* namespaze;
            Type        byval_arg;
            Type        this_arg;
            Class* element_class;
            Class* castClass;
            Class* declaringType;
            Class* parent;

        public:
            Class() = delete;

            auto GetImage() const -> Image* {
                try {
                    return static_cast<Image * (*)(const Class * type)>(address_["il2cpp_class_get_image"])(this);
                } catch (...) {
                    return nullptr;
                }
            }

            auto GetName() const -> std::string {
                try {
                    return static_cast<const char* (*)(const Class * _this)>(address_["il2cpp_class_get_name"])(this);
                } catch (...) {
                    return "";
                }
            }

            auto GetNamespace() const -> std::string {
                try {
                    return static_cast<const char* (*)(const Class * _this)>(address_["il2cpp_class_get_namespace"])(this);
                } catch (...) {
                    return "";
                }
            }

            auto GetParent() const -> Class* {
                try {
                    return static_cast<Class * (*)(const Class * _this)>(address_["il2cpp_class_get_parent"])(this);
                } catch (...) {
                    return nullptr;
                }
            }

            auto EnumFields(std::list<Field*>& fields) -> size_t {
                void* iter = nullptr;
                Field* field;
                do {
                    try {
                        field = static_cast<Field * (*)(Class * _this, void* iter)>(address_["il2cpp_class_get_fields"])(this, &iter);
                        if (field)
                            fields.push_back(field);
                    } catch (...) {
                        field = 0;
                        continue;
                    }
                } while (field);
                return fields.size();
            }

            auto GetFieldFromName(const std::string& name) -> Field* {
                return static_cast<Field * (*)(Class * _this, const char* name)>(address_["il2cpp_class_get_field_from_name"])(this, name.c_str());
            }

            auto EnumMethods(std::list<Method*>& methods) -> size_t {
                void* iter = nullptr;
                Method* field;
                do {
                    try {
                        field = static_cast<Method * (*)(Class * _this, void* iter)>(address_["il2cpp_class_get_methods"])(this, &iter);
                        if (field)
                            methods.push_back(field);
                    } catch (...) {
                        field = 0;
                        continue;
                    }
                } while (field);
                return methods.size();
            }

            auto GetMethodFromName(const std::string& name, const size_t param_count = -1) -> Method* {
                try {
                    return static_cast<Method * (*)(Class * _this, const char* name, size_t param_count)>(address_["il2cpp_class_get_method_from_name"])(this, name.c_str(), param_count);
                } catch (...) {
                    return nullptr;
                }
            }

            static auto GetClassFromName(const std::string& class_name, const std::string& namespaze = "") -> Class* {
                std::list<Assembly*> assemblys;
                Assembly::EnumAssemblys(assemblys);
                for (const auto& assembly : assemblys) {
                    Class* klass{};
                    try {
                        klass = assembly->GetImage()->GetClassFromName(class_name, namespaze);
                    } catch (...) {
                        LOG_WARNING(std::format("assembly异常"));
                        continue;
                    }

                    if (klass == nullptr)
                        continue;
                    if (klass->GetName() != class_name)
                        continue;
                    if (namespaze != "")
                        if (klass->GetNamespace() != namespaze)
                            continue;

                    return klass;
                }
                return nullptr;
            }
        };

        struct Field {
        private:
            const char* name;
            Type* type;
            Class* parent;
            int32_t     offset; // If offset is -1, then it's thread static
            uint32_t    token;

        public:
            Field() = delete;

            template<typename T>
            auto GetStatic() -> T {
                try {
                    T val = 0;
                    static_cast<void(*)(Field * field, void* ptr)>(address_["il2cpp_field_static_get_value"])(this, &val);
                    return val;
                } catch (...) {
                    return T{};
                }
            }

            template<typename T>
            auto SetStatic(T& val) -> void {
                try {
                    static_cast<void(*)(Field * field, void* ptr)>(address_["il2cpp_field_static_set_value"])(this, &val);
                } catch (...) {
                    return;
                }
            }

            auto IsStatic() const -> bool {
                try {
                    return this->GetOffset() == -1 ? true : false;
                } catch (...) {
                    return false;
                }
            }

            auto GetName() const -> std::string {
                try {
                    return static_cast<const char* (*)(const Field * _this)>(address_["il2cpp_field_get_name"])(this);
                } catch (...) {
                    return "";
                }
            }

            auto GetType() const -> Type* {
                try {
                    return static_cast<Type* (*)(const Field * _this)>(address_["il2cpp_field_get_type"])(this);
                } catch (...) {
                    return nullptr;
                }
            }

            auto GetOffset() const -> std::uintptr_t {
                try {
                    return static_cast<size_t (*)(const Field * _this)>(address_["il2cpp_field_get_offset"])(this);
                } catch (...) {
                    return 0;
                }
            }
        };

        struct Method {
        private:
            void (*methodPointer)();
            void* (*invoker_Method)(void (*methodPointer)(), const Method*, void*, void**);
            const char* name;
            Class* klass;
            Type* return_type;

            struct {
                const char* name;
                int32_t     position;
                uint32_t    token;
                Type* parameter_type;
            } *parameters;
        public:
            Method() = delete;

            auto GetName() const -> std::string {
                try {
                    return static_cast<const char* (*)(const Method * _this)>(address_["il2cpp_method_get_name"])(this);
                } catch (...) {
                    return "";
                }
            }

            auto GetRetType() const -> Type* {
                try {
                    return static_cast<Type * (*)(const Method * _this)>(address_["il2cpp_method_get_return_type"])(this);
                } catch (...) {
                    return nullptr;
                }
            }

            auto GetParamCount() const -> size_t {
                try {
                    return reinterpret_cast<size_t(*)(const Method*)>(address_["il2cpp_method_get_param_count"])(this);
                } catch (...) {
                    return 0;
                }
            }

            auto GetParam(const size_t index) const -> Type* {
                try {
                    return static_cast<Type * (*)(const Method * _this, uint32_t)>(address_["il2cpp_method_get_return_type"])(this, index);
                } catch (...) {
                    return nullptr;
                }
            }

            auto GetParamName(const size_t index) const -> std::string {
                try {
                    return static_cast<const char* (*)(const Method * _this, uint32_t)>(address_["il2cpp_method_get_param_name"])(this, index);
                } catch (...) {
                    return "";
                }
            }

            auto EnumParam(std::map<std::string, Type*>& map) const -> size_t {
                try {
                    const size_t count = this->GetParamCount();
                    for (size_t i = 0; i < count; i++)
                        map[this->GetParamName(i)] = this->GetParam(i);
                    return map.size();
                } catch (...) {
                    return map.size();
                }
            }

            auto GetFlags() const -> std::uint32_t {
                try {
                    return reinterpret_cast<std::uint32_t(*)(const Method*, uint32_t*)>(address_["il2cpp_method_get_flags"])(this, nullptr);
                } catch (...) {
                    return 0;
                }
            }

            auto IsStatic() const -> bool { return 0x10 & this->GetFlags(); }

            template<typename OBJ>
            auto Invoke(OBJ* obj, void** params) -> struct Object* {
                try {
                    return static_cast<Object * (*)(Method * _this, void* obj, void** params, Object * *exc)>(address_["il2cpp_runtime_invoke"])(this, obj, params, nullptr);
                } catch (...) {
                    return nullptr;
                }
            }

            auto GetAddress() -> std::uintptr_t {
                try {
                    return reinterpret_cast<std::uintptr_t>(this->methodPointer);
                } catch (...) {
                    return 0;
                }
            }

            static auto GetAddress(const std::string& class_name,
                                   const std::string& method_name,
                                   const size_t       param_count = -1,
                                   const std::string& namespaze = "") -> std::uintptr_t {

                Class* klass{};
                try {
                    klass = Class::GetClassFromName(class_name, namespaze);
                    if (klass == nullptr) {
                        LOG_WARNING(std::format("未找到 \"{}\" 类\n", class_name));
                        return 0;
                    }
                }
                catch (...) {
                    LOG_WARNING(std::format("寻找 \"{}\" 类时发生异常\n", class_name));
                    return 0;
                }

                try {
                    return klass->GetMethodFromName(method_name, param_count)->GetAddress();
                } catch (...) {
                    LOG_WARNING(std::format("未找到 \"{}\" 函数\n", method_name));
                    return 0;
                }
            }
        };

    private:
        inline static HMODULE                                hModule_;
        inline static std::unordered_map<std::string, void*> address_{
            {"CloseZStream", nullptr}, {"CreateZStream", nullptr}, {"DllCanUnloadNow", nullptr},
            {"DllGetActivationFactory", nullptr}, {"Flush", nullptr}, {"ReadZStream", nullptr},
            {"UnityPalGetLocalTimeZoneData", nullptr}, {"UnityPalGetTimeZoneDataForID", nullptr},
            {"UnityPalTimeZoneInfoGetTimeZoneIDs", nullptr}, {"UseUnityPalForTimeZoneInformation", nullptr},
            {"WriteZStream", nullptr}, {"il2cpp_add_internal_call", nullptr}, {"il2cpp_alloc", nullptr},
            {"il2cpp_allocation_granularity", nullptr}, {"il2cpp_array_class_get", nullptr},
            {"il2cpp_array_element_size", nullptr}, {"il2cpp_array_get_byte_length", nullptr},
            {"il2cpp_array_length", nullptr}, {"il2cpp_array_new", nullptr}, {"il2cpp_array_new_full", nullptr},
            {"il2cpp_array_new_specific", nullptr}, {"il2cpp_array_object_header_size", nullptr},
            {"il2cpp_assembly_get_image", nullptr}, {"il2cpp_bounded_array_class_get", nullptr},
            {"il2cpp_capture_memory_snapshot", nullptr}, {"il2cpp_class_array_element_size", nullptr},
            {"il2cpp_class_enum_basetype", nullptr}, {"il2cpp_class_for_each", nullptr},
            {"il2cpp_class_from_il2cpp_type", nullptr}, {"il2cpp_class_from_name", nullptr},
            {"il2cpp_class_from_system_type", nullptr}, {"il2cpp_class_from_type", nullptr},
            {"il2cpp_class_get_assemblyname", nullptr}, {"il2cpp_class_get_bitmap", nullptr},
            {"il2cpp_class_get_bitmap_size", nullptr}, {"il2cpp_class_get_data_size", nullptr},
            {"il2cpp_class_get_declaring_type", nullptr}, {"il2cpp_class_get_element_class", nullptr},
            {"il2cpp_class_get_events", nullptr}, {"il2cpp_class_get_field_from_name", nullptr},
            {"il2cpp_class_get_fields", nullptr}, {"il2cpp_class_get_flags", nullptr},
            {"il2cpp_class_get_image", nullptr}, {"il2cpp_class_get_instance_methods_from_names", nullptr},
            {"il2cpp_class_get_interfaces", nullptr}, {"il2cpp_class_get_method_from_name", nullptr},
            {"il2cpp_class_get_methods", nullptr}, {"il2cpp_class_get_name", nullptr},
            {"il2cpp_class_get_namespace", nullptr}, {"il2cpp_class_get_nested_types", nullptr},
            {"il2cpp_class_get_parent", nullptr}, {"il2cpp_class_get_properties", nullptr},
            {"il2cpp_class_get_property_from_name", nullptr}, {"il2cpp_class_get_rank", nullptr},
            {"il2cpp_class_get_static_field_data", nullptr}, {"il2cpp_class_get_type", nullptr},
            {"il2cpp_class_get_type_token", nullptr}, {"il2cpp_class_get_userdata_offset", nullptr},
            {"il2cpp_class_has_attribute", nullptr}, {"il2cpp_class_has_parent", nullptr},
            {"il2cpp_class_has_references", nullptr}, {"il2cpp_class_instance_size", nullptr},
            {"il2cpp_class_is_abstract", nullptr}, {"il2cpp_class_is_assignable_from", nullptr},
            {"il2cpp_class_is_blittable", nullptr}, {"il2cpp_class_is_enum", nullptr},
            {"il2cpp_class_is_generic", nullptr}, {"il2cpp_class_is_inflated", nullptr},
            {"il2cpp_class_is_interface", nullptr}, {"il2cpp_class_is_subclass_of", nullptr},
            {"il2cpp_class_is_valuetype", nullptr}, {"il2cpp_class_num_fields", nullptr},
            {"il2cpp_class_set_userdata", nullptr}, {"il2cpp_class_value_size", nullptr},
            {"il2cpp_current_thread_get_frame_at", nullptr}, {"il2cpp_current_thread_get_stack_depth", nullptr},
            {"il2cpp_current_thread_get_top_frame", nullptr}, {"il2cpp_current_thread_walk_frame_stack", nullptr},
            {"il2cpp_custom_attrs_construct", nullptr}, {"il2cpp_custom_attrs_free", nullptr},
            {"il2cpp_custom_attrs_from_class", nullptr}, {"il2cpp_custom_attrs_from_method", nullptr},
            {"il2cpp_custom_attrs_get_attr", nullptr}, {"il2cpp_custom_attrs_has_attr", nullptr},
            {"il2cpp_debug_get_method_info", nullptr}, {"il2cpp_debugger_set_agent_options", nullptr},
            {"il2cpp_domain_assembly_open", nullptr}, {"il2cpp_domain_get", nullptr},
            {"il2cpp_domain_get_assemblies", nullptr}, {"il2cpp_exception_from_name_msg", nullptr},
            {"il2cpp_field_get_flags", nullptr}, {"il2cpp_field_get_name", nullptr},
            {"il2cpp_field_get_offset", nullptr}, {"il2cpp_field_get_parent", nullptr},
            {"il2cpp_field_get_type", nullptr}, {"il2cpp_field_get_value", nullptr},
            {"il2cpp_field_get_value_object", nullptr}, {"il2cpp_field_has_attribute", nullptr},
            {"il2cpp_field_is_literal", nullptr}, {"il2cpp_field_set_value", nullptr},
            {"il2cpp_field_set_value_object", nullptr}, {"il2cpp_field_static_get_value", nullptr},
            {"il2cpp_field_static_set_value", nullptr}, {"il2cpp_format_exception", nullptr},
            {"il2cpp_format_stack_trace", nullptr}, {"il2cpp_free", nullptr},
            {"il2cpp_free_captured_memory_snapshot", nullptr}, {"il2cpp_gc_collect", nullptr},
            {"il2cpp_gc_collect_a_little", nullptr}, {"il2cpp_gc_disable", nullptr}, {"il2cpp_gc_enable", nullptr},
            {"il2cpp_gc_foreach_heap", nullptr}, {"il2cpp_gc_get_heap_size", nullptr},
            {"il2cpp_gc_get_max_time_slice_ns", nullptr}, {"il2cpp_gc_get_used_size", nullptr},
            {"il2cpp_gc_has_strict_wbarriers", nullptr}, {"il2cpp_gc_is_disabled", nullptr},
            {"il2cpp_gc_is_incremental", nullptr}, {"il2cpp_gc_set_external_allocation_tracker", nullptr},
            {"il2cpp_gc_set_external_wbarrier_tracker", nullptr}, {"il2cpp_gc_set_max_time_slice_ns", nullptr},
            {"il2cpp_gc_wbarrier_set_field", nullptr}, {"il2cpp_gchandle_foreach_get_target", nullptr},
            {"il2cpp_gchandle_free", nullptr}, {"il2cpp_gchandle_get_target", nullptr},
            {"il2cpp_gchandle_new", nullptr}, {"il2cpp_gchandle_new_weakref", nullptr}, {"il2cpp_get_corlib", nullptr},
            {"il2cpp_get_exception_argument_null", nullptr}, {"il2cpp_image_get_assembly", nullptr},
            {"il2cpp_image_get_class", nullptr}, {"il2cpp_image_get_class_count", nullptr},
            {"il2cpp_image_get_entry_point", nullptr}, {"il2cpp_image_get_filename", nullptr},
            {"il2cpp_image_get_name", nullptr}, {"il2cpp_init", nullptr}, {"il2cpp_init_security", nullptr},
            {"il2cpp_init_utf16", nullptr}, {"il2cpp_is_debugger_attached", nullptr}, {"il2cpp_is_vm_thread", nullptr},
            {"il2cpp_method_get_class", nullptr}, {"il2cpp_method_get_declaring_type", nullptr},
            {"il2cpp_method_get_flags", nullptr}, {"il2cpp_method_get_from_reflection", nullptr},
            {"il2cpp_method_get_name", nullptr}, {"il2cpp_method_get_object", nullptr},
            {"il2cpp_method_get_param", nullptr}, {"il2cpp_method_get_param_count", nullptr},
            {"il2cpp_method_get_param_name", nullptr}, {"il2cpp_method_get_return_type", nullptr},
            {"il2cpp_method_get_token", nullptr}, {"il2cpp_method_has_attribute", nullptr},
            {"il2cpp_method_is_generic", nullptr}, {"il2cpp_method_is_inflated", nullptr},
            {"il2cpp_method_is_instance", nullptr}, {"il2cpp_monitor_enter", nullptr}, {"il2cpp_monitor_exit", nullptr},
            {"il2cpp_monitor_pulse", nullptr}, {"il2cpp_monitor_pulse_all", nullptr},
            {"il2cpp_monitor_try_enter", nullptr}, {"il2cpp_monitor_try_wait", nullptr},
            {"il2cpp_monitor_wait", nullptr}, {"il2cpp_object_get_class", nullptr}, {"il2cpp_object_get_size", nullptr},
            {"il2cpp_object_get_virtual_method", nullptr}, {"il2cpp_object_header_size", nullptr},
            {"il2cpp_object_new", nullptr}, {"il2cpp_object_unbox", nullptr},
            {"il2cpp_offset_of_array_bounds_in_array_object_header", nullptr},
            {"il2cpp_offset_of_array_length_in_array_object_header", nullptr},
            {"il2cpp_override_stack_backtrace", nullptr}, {"il2cpp_profiler_install", nullptr},
            {"il2cpp_profiler_install_allocation", nullptr}, {"il2cpp_profiler_install_enter_leave", nullptr},
            {"il2cpp_profiler_install_fileio", nullptr}, {"il2cpp_profiler_install_gc", nullptr},
            {"il2cpp_profiler_install_thread", nullptr}, {"il2cpp_profiler_set_events", nullptr},
            {"il2cpp_property_get_flags", nullptr}, {"il2cpp_property_get_get_method", nullptr},
            {"il2cpp_property_get_name", nullptr}, {"il2cpp_property_get_parent", nullptr},
            {"il2cpp_property_get_set_method", nullptr}, {"il2cpp_raise_exception", nullptr},
            {"il2cpp_register_debugger_agent_transport", nullptr}, {"il2cpp_register_errorlog_callback", nullptr},
            {"il2cpp_register_log_callback", nullptr}, {"il2cpp_resolve_icall", nullptr},
            {"il2cpp_runtime_class_init", nullptr}, {"il2cpp_runtime_invoke", nullptr},
            {"il2cpp_runtime_invoke_convert_args", nullptr}, {"il2cpp_runtime_object_init", nullptr},
            {"il2cpp_runtime_object_init_exception", nullptr},
            {"il2cpp_runtime_unhandled_exception_policy_set", nullptr}, {"il2cpp_set_commandline_arguments", nullptr},
            {"il2cpp_set_commandline_arguments_utf16", nullptr}, {"il2cpp_set_config", nullptr},
            {"il2cpp_set_config_dir", nullptr}, {"il2cpp_set_config_utf16", nullptr}, {"il2cpp_set_data_dir", nullptr},
            {"il2cpp_set_default_thread_affinity", nullptr}, {"il2cpp_set_find_plugin_callback", nullptr},
            {"il2cpp_set_memory_callbacks", nullptr}, {"il2cpp_set_temp_dir", nullptr}, {"il2cpp_shutdown", nullptr},
            {"il2cpp_start_gc_world", nullptr}, {"il2cpp_stats_dump_to_file", nullptr},
            {"il2cpp_stats_get_value", nullptr}, {"il2cpp_stop_gc_world", nullptr}, {"il2cpp_string_chars", nullptr},
            {"il2cpp_string_intern", nullptr}, {"il2cpp_string_is_interned", nullptr},
            {"il2cpp_string_length", nullptr}, {"il2cpp_string_new", nullptr}, {"il2cpp_string_new_len", nullptr},
            {"il2cpp_string_new_utf16", nullptr}, {"il2cpp_string_new_wrapper", nullptr},
            {"il2cpp_thread_attach", nullptr}, {"il2cpp_thread_current", nullptr}, {"il2cpp_thread_detach", nullptr},
            {"il2cpp_thread_get_all_attached_threads", nullptr}, {"il2cpp_thread_get_frame_at", nullptr},
            {"il2cpp_thread_get_stack_depth", nullptr}, {"il2cpp_thread_get_top_frame", nullptr},
            {"il2cpp_thread_walk_frame_stack", nullptr}, {"il2cpp_type_equals", nullptr},
            {"il2cpp_type_get_assembly_qualified_name", nullptr}, {"il2cpp_type_get_attrs", nullptr},
            {"il2cpp_type_get_class_or_element_class", nullptr}, {"il2cpp_type_get_name", nullptr},
            {"il2cpp_type_get_name_chunked", nullptr}, {"il2cpp_type_get_object", nullptr},
            {"il2cpp_type_get_type", nullptr}, {"il2cpp_type_is_byref", nullptr},
            {"il2cpp_type_is_pointer_type", nullptr}, {"il2cpp_type_is_static", nullptr},
            {"il2cpp_unhandled_exception", nullptr}, {"il2cpp_unity_install_unitytls_interface", nullptr},
            {"il2cpp_unity_liveness_calculation_begin", nullptr}, {"il2cpp_unity_liveness_calculation_end", nullptr},
            {"il2cpp_unity_liveness_calculation_from_root", nullptr},
            {"il2cpp_unity_liveness_calculation_from_statics", nullptr}, {"il2cpp_value_box", nullptr}
        };
    };

    inline auto CSharper::SetMap(std::unordered_map<std::string, void*>& map) -> void {
        address_ = &map;
        if (il2cpp) {
            methodAddress_["Camera.WorldToScreenPoint"] = Il2cpp::Method::GetAddress("Camera", "WorldToScreenPoint", 2);
            methodAddress_["Camera.ScreenToWorldPoint"] = Il2cpp::Method::GetAddress("Camera", "ScreenToWorldPoint", 1);
            methodAddress_["Camera.get_main"] = Il2cpp::Method::GetAddress("Camera", "get_main", 0);
            methodAddress_["Camera.get_current"] = Il2cpp::Method::GetAddress("Camera", "get_current", 0);
            methodAddress_["Camera.get_allCamerasCount"] = Il2cpp::Method::GetAddress("Camera",
                "get_allCamerasCount",
                0);
            methodAddress_["Camera.get_allCameras"] = Il2cpp::Method::GetAddress("Camera", "get_allCameras", 0);
            methodAddress_["Camera.get_depth"] = Il2cpp::Method::GetAddress("Camera", "get_depth", 0);
            methodAddress_["Camera.set_depth"] = Il2cpp::Method::GetAddress("Camera", "set_depth", 1);
            methodAddress_["Transform.get_position"] = Il2cpp::Method::GetAddress("Transform", "get_position", 0);
            methodAddress_["Transform.set_position"] = Il2cpp::Method::GetAddress("Transform", "set_position", 1);
            methodAddress_["GameObject.get_transform"] = Il2cpp::Method::GetAddress("GameObject", "get_transform", 0, "UnityEngine");
            methodAddress_["GameObject.get_tag"] = Il2cpp::Method::GetAddress("GameObject", "get_tag", 0, "UnityEngine");
            methodAddress_["Object.Destroy"] = Il2cpp::Method::GetAddress("Object", "Destroy", 1, "UnityEngine");
            methodAddress_["Object.DestroyImmediate"] = Il2cpp::Method::GetAddress("Object", "DestroyImmediate", 1, "UnityEngine");
            methodAddress_["Component.get_transform"] = Il2cpp::Method::GetAddress("Component", "get_transform", 0, "UnityEngine");
            methodAddress_["Component.get_tag"] = Il2cpp::Method::GetAddress("Component", "get_tag", 0, "UnityEngine");
            methodAddress_["List`1.get_Count"] = Il2cpp::Method::GetAddress("List`1", "get_Count", 0, "System.Collections.Generic");
            methodAddress_["List`1.Add"] = Il2cpp::Method::GetAddress("List`1", "Add", 1, "System.Collections.Generic");
            methodAddress_["List`1.get_Item"] = Il2cpp::Method::GetAddress("List`1", "get_Item", 1, "System.Collections.Generic");
            methodAddress_["List`1.set_Item"] = Il2cpp::Method::GetAddress("List`1", "set_Item", 2, "System.Collections.Generic");
            methodAddress_["List`1.Remove"] = Il2cpp::Method::GetAddress("List`1", "Remove", 1, "System.Collections.Generic");
        }
        else {
            methodAddress_["Camera.WorldToScreenPoint"] = Mono::Method::GetAddress("Camera", "WorldToScreenPoint", 2);
            methodAddress_["Camera.ScreenToWorldPoint"] = Mono::Method::GetAddress("Camera", "ScreenToWorldPoint", 1);
            methodAddress_["Camera.get_main"] = Mono::Method::GetAddress("Camera", "get_main", 0);
            methodAddress_["Camera.get_current"] = Mono::Method::GetAddress("Camera", "get_current", 0);
            methodAddress_["Camera.get_allCamerasCount"] = Mono::Method::GetAddress("Camera", "get_allCamerasCount", 0);
            methodAddress_["Camera.get_allCameras"] = Mono::Method::GetAddress("Camera", "get_allCameras", 0);
            methodAddress_["Camera.get_depth"] = Mono::Method::GetAddress("Camera", "get_depth", 0);
            methodAddress_["Camera.set_depth"] = Mono::Method::GetAddress("Camera", "set_depth", 1);
            methodAddress_["Transform.get_position"] = Mono::Method::GetAddress("Transform", "get_position", 0);
            methodAddress_["Transform.set_position"] = Mono::Method::GetAddress("Transform", "set_position", 1);
            methodAddress_["GameObject.get_transform"] = Mono::Method::GetAddress("GameObject", "get_transform", 0);
            methodAddress_["GameObject.get_tag"] = Mono::Method::GetAddress("GameObject", "get_tag", 0);
            methodAddress_["Object.Destroy"] = Mono::Method::GetAddress("Object", "Destroy", 1, "UnityEngine");
            methodAddress_["Object.DestroyImmediate"] = Mono::Method::GetAddress("Object", "DestroyImmediate", 1, "UnityEngine");
            methodAddress_["Component.get_transform"] = Mono::Method::GetAddress("Component", "get_transform", 0, "UnityEngine");
            methodAddress_["Component.get_tag"] = Mono::Method::GetAddress("Component", "get_tag", 0, "UnityEngine");
            methodAddress_["List`1.get_Count"] = Mono::Method::GetAddress("List`1", "get_Count", 0, "System.Collections.Generic");
            methodAddress_["List`1.Add"] = Mono::Method::GetAddress("List`1", "Add", 1, "System.Collections.Generic");
            methodAddress_["List`1.get_Item"] = Mono::Method::GetAddress("List`1", "get_Item", 1, "System.Collections.Generic");
            methodAddress_["List`1.set_Item"] = Mono::Method::GetAddress("List`1", "set_Item", 2, "System.Collections.Generic");
            methodAddress_["List`1.Remove"] = Mono::Method::GetAddress("List`1", "Remove", 1, "System.Collections.Generic");
        }
        for (auto& [name, address] : methodAddress_) {
            if (address == 0) {
                LOG_WARNING(std::format("Unity 函数 \"{}\" 无法获取到地址\n", name));
            }
        }
    }
}
