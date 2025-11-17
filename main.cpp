#include "engine/Helper.h"
enum class Language {
English,
Turkish};

Language currentLanguage = Language::English; // Default language is English
const char* Translate(const char* english, const char* turkish) {
switch (currentLanguage) {
case Language::Turkish: return turkish;
default: return english;}}

static float RadarZoom = 1.50f;
static float LightAngle = 43.0f;
static float LightDistance = 18.0f;
static int isCount = 1;

static bool enableVisCheck = true;
static ImVec4 visibleColor    = ImVec4(1.0f, 0.1f, 0.1f, 1.0f);
static ImVec4 notVisibleColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

static ImVec4 countColor = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
static ImVec4 borderColor = ImVec4(0.78f, 0.78f, 0.78f, 0.78f);
static float cornerRadius = 10.0f;
static float textSize = 27.3f;
static float padding = 10.0f;
static ImVec4 textColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
static ImVec4 fovcol = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

float VehicleDist = 400.0f;
float LootBoxDist = 200.0f;
float LootDist = 150.0f;
float CrateItemsDist = 50.0f;
static ImVec4 GrenadeCol = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);

bool showCrosshair;
ImVec4 crosshairColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
float crosshairSize = 10.0f;
float crosshairThickness = 2.0f; 
bool sniperMode;
static int counterStyle = 0;
static int espStyle = 0;
#include <ctime>
#include <cstdio>

#include <chrono>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

auto calculateRemainingTime = [](const std::string& expirationDate) {
    std::tm tm = {};
    std::istringstream ss(expirationDate);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    auto expirationTime = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    auto now = std::chrono::system_clock::now();
    auto remainingTime = expirationTime - now;
    auto remainingSeconds = std::chrono::duration_cast<std::chrono::seconds>(remainingTime).count();

    if (remainingSeconds > 0) {
        int days = remainingSeconds / (60 * 60 * 24);
        remainingSeconds %= (60 * 60 * 24);
        int hours = remainingSeconds / (60 * 60);
        remainingSeconds %= (60 * 60);
        int minutes = remainingSeconds / 60;
        int seconds = remainingSeconds % 60;
        return std::make_tuple(days, hours, minutes, seconds);
    }
    else {
        return std::make_tuple(0, 0, 0, 0);
    }
};
#include <chrono>
#include <fstream>


bool ResetGuest;
bool DeviceBanFix;
bool SkipGameUpdate;

std::string GetSystemProperty(const char* property) {
    char value[PROP_VALUE_MAX];
    __system_property_get(property, value);
    return std::string(value);
}

bool isSpawnON  = false;


template <class T> void GetAllActors(std::vector<T*>& Actors) {
UGameplayStatics* gGameplayStatics = (UGameplayStatics*)gGameplayStatics->StaticClass();
auto GWorld = GetWorld();
if (GWorld) {
TArray<AActor*> Actors2;
gGameplayStatics->GetAllActorsOfClass((UObject*)GWorld, T::StaticClass(), &Actors2);
for (int i = 0; i < Actors2.Num(); i++) {
Actors.push_back((T*)Actors2[i]);
}
}
}

#include "skin/draw.h"
#include "skin/local.h"

////////esp drawing
void MONSTEResp(ImDrawList *draw, int screenWidth, int screenHeight) {			
glWidth = screenWidth;
glHeight = screenHeight;		
if(!g_Token.empty() && !g_Auth.empty() && g_Token == g_Auth) {	

	if (showCrosshair) {
    ImVec2 screenCenter = ImVec2(screenWidth / 2.0f, screenHeight / 2.0f);
    float halfSize = crosshairSize / 2.0f;
    draw->AddLine(ImVec2(screenCenter.x - halfSize, screenCenter.y), 
                  ImVec2(screenCenter.x + halfSize, screenCenter.y), 
                  ImColor(crosshairColor), crosshairThickness);
    draw->AddLine(ImVec2(screenCenter.x, screenCenter.y - halfSize), 
                  ImVec2(screenCenter.x, screenCenter.y + halfSize), 
                  ImColor(crosshairColor), crosshairThickness);
}
	
/////////actor factor

ImDrawList* drawList = ImGui::GetBackgroundDrawList();
ImVec2 screenSize = ImGui::GetIO().DisplaySize;

// Konum ayarları (biraz sola ve yukarı)
float x = screenSize.x * 0.12f;     // %25 yerine %18 → sola kaydırıldı
float y = screenSize.y - 66.0f;     // -40 yerine -60 → yukarı kaydırıldı

// Yazı içeriği
const char* text = "DOLLAR ESP v1.0";

// Küçük fontla yazmak için custom font (eğer eklediysen)
ImFont* smallFont = ImGui::GetFont(); // mevcut fontu kullan, istersen özel font da tanımlayabilirim

// Gölge (isteğe bağlı)
drawList->AddText(smallFont, 20.0f, ImVec2(x + 1, y + 1), IM_COL32(0, 0, 0, 160), text);

// Kırmızı küçük yazı
drawList->AddText(smallFont, 20.0f, ImVec2(x, y), IM_COL32(255, 0, 0, 220), text);
int totalEnemies = 0, totalBots = 0;
ASTExtraPlayerController* localController = nullptr;
ASTExtraPlayerCharacter* localPlayer = nullptr;

ASTExtraPlayerController *asw = 0;
bool foundasw = false;

auto Actors = getActors();
		for (int i = 0; i < Actors.size() && !foundasw; i++) {
            auto Actor = Actors[i];
            if (isObjectInvalid(Actor))
                continue;

            if (Actor->IsA(ASTExtraPlayerController::StaticClass())) {
                asw = (ASTExtraPlayerController *) Actor;
				foundasw = true;
                break;
            }
        }

        if (asw) {
	        if(!isSpawnON){
	        isSpawnON = true;



	        }
			
			} else {
			if(isSpawnON){
	        isSpawnON = false;
// OFF
	ModSkinn = false;
	KillMessage = false;
	DeasBoxSkin = false;
			
			

			}
	}
        for (int i = 0; i < Actors.size(); i++) {
            auto Actor = Actors[i];
            if (isObjectInvalid(Actor))
                continue;

            if (Actor->IsA(ASTExtraPlayerController::StaticClass())) {
                localController = (ASTExtraPlayerController *) Actor;
                break;
            }
        }

size_t actorCount = Actors.size();  

for (size_t i = 0; i < actorCount; i++) {
auto Actor = Actors[i];
if (isObjectInvalid(Actor)) continue;
if (Actor->IsA(ASTExtraPlayerController::StaticClass())) {
localController = static_cast<ASTExtraPlayerController*>(Actor);
break;}}
if (localController) {

for (size_t i = 0; i < actorCount; i++) {
auto Actor = Actors[i];
if (isObjectInvalid(Actor)) continue;
if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
auto* PlayerCharacter = static_cast<ASTExtraPlayerCharacter*>(Actor);
if (PlayerCharacter->PlayerKey == localController->PlayerKey) {
localPlayer = PlayerCharacter;
break;}}}

if (localPlayer) {
if (localPlayer->PartHitComponent) {
auto ConfigCollisionDistSqAngles = localPlayer->PartHitComponent->ConfigCollisionDistSqAngles;
for (int j = 0; j < ConfigCollisionDistSqAngles.Num(); j++) {
ConfigCollisionDistSqAngles[j].Angle = 180.0f;}
localPlayer->PartHitComponent->ConfigCollisionDistSqAngles = ConfigCollisionDistSqAngles;}
/////
///////////Ipad Mode
auto PlayerCameraManager = localController->PlayerCameraManager;
if (IpadModu)  {    
localPlayer->ThirdPersonCameraComponent->SetFieldOfView(IpadModu2);}  		
	
//////////Magic Bullet
if (isMagicBullet) {
uintptr_t Mesh = *(uintptr_t *)((uintptr_t)localPlayer + Offsets::mesh11);
if (Mesh != 0){
uintptr_t Skeletal = *(uintptr_t *)(Mesh + Offsets::Skeletal);
if (Skeletal != 0){
uintptr_t Asset = *(uintptr_t *)(Skeletal + Offsets::Asset);
if (Asset != 0){
uintptr_t ArraySkeletal = *(uintptr_t *)(Asset + Offsets::ArraySkeletal);
if (ArraySkeletal != 0){
uintptr_t SkeletalBodySetup = *(uintptr_t *)(ArraySkeletal + sizeof(uintptr_t) * 14);
if (SkeletalBodySetup != 0){
uintptr_t BoxElems = *(uintptr_t *)(SkeletalBodySetup + Offsets::ArraySkeletal);
if (BoxElems != 0){
*(float *)(BoxElems + Offsets::BoxElems1) = 200.0f;//55
*(float *)(BoxElems + Offsets::BoxElems2) = 200.0f;//75
*(float *)(BoxElems + Offsets::BoxElems3) = 200.0f;//95
}}}}}}}

///////////Aimbot	
if (AimFov) {
draw->AddCircle(ImVec2(glWidth / 2, glHeight / 2), AimSize*0.5f, ImGui::ColorConvertFloat4ToU32(fovcol), 100, 1.0f);				
}				
if (AimBot) {
    ASTExtraPlayerCharacter* Target = GetTargetForAimBot();
    if (Target){
bool triggerOk = false;
        switch (Trigger) {
            case EAimTrigger::Shooting:
                triggerOk = localPlayer->bIsWeaponFiring;
                break;
            case EAimTrigger::Scoping:
                triggerOk = localPlayer->bIsGunADS;
                break;
            case EAimTrigger::Any:
                triggerOk = localPlayer->bIsWeaponFiring || localPlayer->bIsGunADS;
                break;
            default:
                triggerOk = true;
        }
         if (triggerOk)
       {
        FVector targetAimPos = Target->GetBonePos("Head", {});
	
		auto WeaponManagerComponent = localPlayer->WeaponManagerComponent;
if (WeaponManagerComponent) {
auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
if ((int) propSlot.GetValue() >= 1 && (int) propSlot.GetValue() <= 3) {
auto CurrentWeaponReplicated = (ASTExtraShootWeapon *) WeaponManagerComponent->CurrentWeaponReplicated;
if (CurrentWeaponReplicated) {
auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;
if (ShootWeaponComponent) {
UShootWeaponEntity *ShootWeaponEntityComponent = ShootWeaponComponent->ShootWeaponEntityComponent;
if (ShootWeaponEntityComponent) {
ASTExtraVehicleBase *CurrentVehicle = Target->CurrentVehicle;
if (CurrentVehicle) {
FVector LinearVelocity = CurrentVehicle->ReplicatedMovement.LinearVelocity;
float dist = localPlayer->GetDistanceTo(Target);
auto timeToTravel = dist / ShootWeaponEntityComponent->BulletRange;
targetAimPos = UKismetMathLibrary::Add_VectorVector(
targetAimPos, UKismetMathLibrary::Multiply_VectorFloat(
LinearVelocity, timeToTravel));
} else {
FVector Velocity = Target->GetVelocity();
float dist = localPlayer->GetDistanceTo(Target);
auto timeToTravel = dist / ShootWeaponEntityComponent->BulletRange;
targetAimPos = UKismetMathLibrary::Add_VectorVector(
targetAimPos, UKismetMathLibrary::Multiply_VectorFloat(
Velocity, timeToTravel));}
if (AimBot) {
if (g_LocalPlayer->bIsGunADS) {
if (g_LocalPlayer->bIsWeaponFiring) {
float dist = localPlayer->GetDistanceTo(Target)/ 100.0f;
targetAimPos.Z -= dist * Config.AimBot.Recc;}}}
localController->SetControlRotation(ToRotator(localController->PlayerCameraManager->CameraCache.POV.Location, targetAimPos), "");
}}}}}}}}////////// esp
#include "esp.h"

#define IM_CLAMP(V, MN, MX) ((V) < (MN) ? (MN) : (V) > (MX) ? (MX) : (V))
namespace Settings{
static int Tab = 1;}

////////// save settings
static char SaveSettings[128];
void loadConfig(){
int fd = open("/data/data/com.pubg.krmobile/SaveSettings.ini", O_RDONLY);
if (fd != -1){
read(fd, &Linee, sizeof(Linee)); 
read(fd, &Skeleton, sizeof(Skeleton));
read(fd, &Info, sizeof(Info));
read(fd, &BoxF, sizeof(BoxF));
read(fd, &IpadModu, sizeof(IpadModu));
read(fd, &Trigger, sizeof(Trigger));
read(fd, &Bomba, sizeof(Bomba));
read(fd, &LootBox, sizeof(LootBox));
read(fd, &Alert, sizeof(Alert));
read(fd, &IpadModu2, sizeof(IpadModu2));
read(fd, &Radar, sizeof(Radar));
read(fd, &Weapon, sizeof(Weapon));
read(fd, &Vehicle, sizeof(isVehicle));
read(fd, &AimBot, sizeof(AimBot));
read(fd, &Bullet, sizeof(Bullet));
read(fd, &AimFov, sizeof(AimFov));
read(fd, &AimDist, sizeof(AimDist));
read(fd, &AimSize, sizeof(AimSize));
read(fd, &Knock, sizeof(Knock));
read(fd, &Bots2, sizeof(Bots2));
read(fd, &AirDrop, sizeof(AirDrop));
read(fd, &isDrawAlert, sizeof(isDrawAlert));
read(fd, &isMagicBullet, sizeof(isMagicBullet));
read(fd, &RadarZoom, sizeof(RadarZoom));
read(fd, &LightAngle, sizeof(LightAngle));
read(fd, &LightDistance, sizeof(LightDistance));
read(fd, &enableVisCheck, sizeof(enableVisCheck));
read(fd, &visibleColor, sizeof(visibleColor));
read(fd, &notVisibleColor, sizeof(notVisibleColor));
read(fd, &countColor, sizeof(countColor));
read(fd, &borderColor, sizeof(borderColor));
read(fd, &textColor, sizeof(textColor));
read(fd, &cornerRadius, sizeof(cornerRadius));
read(fd, &textSize, sizeof(textSize));
read(fd, &padding, sizeof(padding));
read(fd, &fovcol, sizeof(fovcol));
read(fd, &VehicleDist, sizeof(VehicleDist));
read(fd, &LootBoxDist, sizeof(LootBoxDist));
read(fd, &LootDist, sizeof(LootDist));
read(fd, &GrenadeCol, sizeof(GrenadeCol));
read(fd, &showCrosshair, sizeof(showCrosshair));
read(fd, &crosshairColor, sizeof(crosshairColor));
read(fd, &crosshairSize, sizeof(crosshairSize));
read(fd, &CrateItemsDist, sizeof(CrateItemsDist));
read(fd, &LootBoxItems, sizeof(LootBoxItems));
read(fd, &counterStyle, sizeof(counterStyle));
read(fd, &crosshairThickness, sizeof(crosshairThickness));
read(fd, &currentLanguage, sizeof(currentLanguage));
///

read(fd, &showCrosshair, sizeof(DeasBoxSkin));
read(fd, &crosshairColor, sizeof(KillMessage));
read(fd, &crosshairSize, sizeof(ModSkinn));
///
read(fd, &SaveSettings, sizeof(SaveSettings));
close(fd);}}

void saveConfig(){
int fd = open("/data/data/com.pubg.krmobile/SaveSettings.ini", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
if (fd != -1){
write(fd, &Linee, sizeof(Linee));
write(fd, &Skeleton, sizeof(Skeleton));
write(fd, &Info, sizeof(Info));
write(fd, &BoxF, sizeof(BoxF));
write(fd, &IpadModu, sizeof(IpadModu));
write(fd, &Trigger, sizeof(Trigger));
write(fd, &Bomba, sizeof(Bomba));		
write(fd, &LootBox, sizeof(LootBox));
write(fd, &Alert, sizeof(Alert));
write(fd, &IpadModu2, sizeof(IpadModu2));
write(fd, &Radar, sizeof(Radar));
write(fd, &Weapon, sizeof(Weapon));
write(fd, &Vehicle, sizeof(isVehicle));
write(fd, &AimBot, sizeof(AimBot));
write(fd, &Bullet, sizeof(Bullet));
write(fd, &AimFov, sizeof(AimFov));
write(fd, &AimDist, sizeof(AimDist));
write(fd, &AimSize, sizeof(AimSize));
write(fd, &Knock, sizeof(Knock));
write(fd, &Bots2, sizeof(Bots2));
write(fd, &AirDrop, sizeof(AirDrop));
write(fd, &isDrawAlert, sizeof(isDrawAlert));
write(fd, &isMagicBullet, sizeof(isMagicBullet));
write(fd, &RadarZoom, sizeof(RadarZoom));
write(fd, &LightAngle, sizeof(LightAngle));
write(fd, &LightDistance, sizeof(LightDistance));
write(fd, &enableVisCheck, sizeof(enableVisCheck));
write(fd, &visibleColor, sizeof(visibleColor));
write(fd, &notVisibleColor, sizeof(notVisibleColor));
write(fd, &countColor, sizeof(countColor));
write(fd, &borderColor, sizeof(borderColor));
write(fd, &textColor, sizeof(textColor));
write(fd, &cornerRadius, sizeof(cornerRadius));
write(fd, &textSize, sizeof(textSize));
write(fd, &padding, sizeof(padding));
write(fd, &fovcol, sizeof(fovcol));
write(fd, &VehicleDist, sizeof(VehicleDist));
write(fd, &LootBoxDist, sizeof(LootBoxDist));
write(fd, &LootDist, sizeof(LootDist));
write(fd, &GrenadeCol, sizeof(GrenadeCol));
write(fd, &showCrosshair, sizeof(showCrosshair));
write(fd, &crosshairColor, sizeof(crosshairColor));
write(fd, &crosshairSize, sizeof(crosshairSize));
write(fd, &CrateItemsDist, sizeof(CrateItemsDist));
write(fd, &LootBoxItems, sizeof(LootBoxItems));
write(fd, &counterStyle, sizeof(counterStyle));
write(fd, &crosshairThickness, sizeof(crosshairThickness));
write(fd, &currentLanguage, sizeof(currentLanguage));
write(fd, &showCrosshair, sizeof(DeasBoxSkin));
write(fd, &crosshairColor, sizeof(KillMessage));
write(fd, &crosshairSize, sizeof(ModSkinn));
write(fd, &SaveSettings, sizeof(SaveSettings));
close(fd);}}

//////////Menu helper
#include "engine/Menu.h"
//////////EGL
EGLBoolean (*orig_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
EGLBoolean _eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);
if (glWidth <= 0 || glHeight <= 0)
return orig_eglSwapBuffers(dpy, surface);

if (!g_App)
return orig_eglSwapBuffers(dpy, surface);

screenWidth = ANativeWindow_getWidth(g_App->window);
screenHeight = ANativeWindow_getHeight(g_App->window);
density = AConfiguration_getDensity(g_App->config);

/////////Menu load
	if (!initImGui) {	
	InitTexture();
    ImGui::CreateContext();	
 	FloatBall = ImAgeHeadFile(logo, sizeof(logo));
    ImGuiStyle& style = ImGui::GetStyle(); 
    
    style.WindowRounding = 3.8f;       
    style.FramePadding = ImVec2(5, 2.5);
    style.FrameRounding = 3.3f; 
    style.FrameBorderSize = 1.0f;
	style.WindowBorderSize = 1.3f;
    ImGui::GetStyle().ScaleAllSizes(2.0f);
    style.WindowTitleAlign = ImVec2(0.5, 0.5); 
        ImVec4 *colors = style.Colors;
    colors[ImGuiCol_Text]                   = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border]                 = ImVec4(0.80f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.80f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.80f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.06f, 0.06f, 0.06f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.81f, 0.83f, 0.81f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.80f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.80f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.80f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.60f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_Separator]              = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.60f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.60f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.80f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.60f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TabActive]              = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.10f, 0.10f, 0.10f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
ImGui_ImplAndroid_Init();
ImGui_ImplOpenGL3_Init(oxorany("#version 300 es"));
ImGuiIO &io = ImGui::GetIO();

io.ConfigWindowsMoveFromTitleBarOnly = false;
static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
ImFontConfig icons_config;
static const ImWchar ranges[] =
{
    0x20, 0xFF,
    0x2010, 0x205E,
    0x0600, 0x06FF,
    0xFE00, 0xFEFF,   
    0,
};  
static const ImWchar redefinitio[] =
{
    0x0020, 0x00FF,
    0x2010, 0x205E,
    0x0600, 0x06FF,
    0xFE00, 0xFEFF,   
    0,
};  
ImFontConfig CustomFont;
CustomFont.FontDataOwnedByAtlas = false;
icons_config.MergeMode = true;
icons_config.PixelSnapH = true;
icons_config.OversampleH = 3;
icons_config.OversampleV = 3;
io.FontGlobalScale = 1.2f;


    Android_LoadSystemFont(23);
    io.Fonts->AddFontFromFileTTF("fa-solid-900.ttf", 18.0f, &icons_config, icons_ranges);
    io.Fonts->Build();

monster = io.Fonts->AddFontFromMemoryCompressedTTF(monster_data, monster_size, 25.f, NULL, &ranges[0]); 
ImFontConfig font_cfg;
font_cfg.SizePixels = 20.0f;
io.Fonts->AddFontDefault(&font_cfg); 

memset(&Config, 0, sizeof(sConfig));
for (auto &i : items_data) {
for (auto &item : i["Items"]) {
int r, g, b;
sscanf(item["itemTextColor"].get<std::string>().c_str(), "#%02X%02X%02X", &r, &g, &b);
ItemColors[item["itemId"].get<int>()] = CREATE_COLOR(r, g, b, 255);
}}
initImGui = true;
}

ImGuiIO &io = ImGui::GetIO();
ImGui_ImplOpenGL3_NewFrame();
ImGui_ImplAndroid_NewFrame(glWidth, glHeight);
ImGui::NewFrame();
MONSTEResp(ImGui::GetBackgroundDrawList(), glWidth, glHeight);

if (!g_Token.empty() && !g_Auth.empty() && g_Token == g_Auth) {		
ImGui::SetNextWindowSize(ImVec2((float) glWidth * 0.54f, (float) glHeight * 0.81f), ImGuiCond_Once);
ImGui::Begin("DOLLAR MOD | PUBG MOBILE v4.1", 0, ImGuiWindowFlags_NoSavedSettings);

     static int espTab = 1;
     static int aimTab = 1;

ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.0f);
ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 15.0f);
ImGui::BeginChild("x", ImVec2(170, 0), true);
ImGui::PopStyleVar(2);
auto Pos = ImGui::GetWindowPos();
ImDrawList *draw_list = ImGui::GetWindowDrawList();
ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {15,15});
if (ImGui::BeginChild("##LuxH7", ImVec2(210, -1), false, ImGuiWindowFlags_NoScrollbar)) {
DrawLogo({Pos.x + 83, Pos.y + 46}, 80);
ImGui::SetCursorPos({0, 78});

ImGui::Separator();	
static int tab = 1;
if (ImGui::Button(Translate("Player ESP", "Oyuncu ESP"), ImVec2(140, 40))) {
Settings::Tab = 1;}
ImGui::Spacing();
    
if (ImGui::Button(Translate("Aimbot", "Aimbot"), ImVec2(140, 40))) {
Settings::Tab = 2;}
ImGui::Spacing();
    
if (ImGui::Button(Translate("Items", "Eşyalar"), ImVec2(140, 40))) {
Settings::Tab = 3;}
ImGui::Spacing();
    
if (ImGui::Button(Translate("Skins", "Desenler"), ImVec2(140, 40))) {
Settings::Tab = 4;}
  
ImGui::Spacing();	
ImGui::Spacing();	
    const char* languages[] = {"English", "Türkçe"};
    int langIndex = static_cast<int>(currentLanguage);
    if (ImGui::Combo(Translate(" ", " "), &langIndex, languages, IM_ARRAYSIZE(languages))) {
        currentLanguage = static_cast<Language>(langIndex);
    }	
ImGui::Checkbox(Translate("Weapon", "Silah"), &Weapon);
ImGui::Checkbox(Translate("Vehicle", "Araç"), &isVehicle);
ImGui::Text(Translate("[FPS: %.1f]", "[FPS: %.1f]"), ImGui::GetIO().Framerate); 
}
ImGui::EndChild();
ImGui::EndChild();
ImGui::SameLine();
ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.0f);
ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 15.0f);
				
ImGui::BeginChild("mainchild", ImVec2(0, 0), true);
ImGui::PopStyleVar(2);

if (Settings::Tab == 1) {
float button_rounding = 4.5f;
ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, button_rounding);
if(ImGui::Button(Translate("ESP Control","ESP Kontrolü"))) { espTab = 1; }
ImGui::SameLine();
if(ImGui::Button(Translate("Settings Esp","Esp Ayarları"))) { espTab = 2; }
ImGui::PopStyleVar();
if (espTab == 1) {

ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), Translate("ESP Features:", "ESP Özellikleri:"));
ImGui::Separator();
if (ImGui::BeginTable("esp_features", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
    ImGui::TableNextColumn(); ImGui::Checkbox(Translate("Character Info", "Karakter Bilgisi"), &Info);
    ImGui::TableNextColumn(); ImGui::Checkbox(Translate("Player Line", "Oyuncu Çizgisi"), &Linee);
    ImGui::TableNextColumn(); ImGui::Checkbox(Translate("Player Bone", "Oyuncu Kemikleri"), &Skeleton);
    ImGui::TableNextColumn(); ImGui::Checkbox(Translate("Player Box", "Oyuncu Kutusu"), &BoxF);
    ImGui::TableNextColumn(); ImGui::Checkbox(Translate("Loot Crate", "Loot Sandığı"), &LootBox);
	ImGui::TableNextColumn(); ImGui::Checkbox(Translate("Crate Items", "Sandık İtemleri"), &LootBoxItems);
    ImGui::TableNextColumn(); ImGui::Checkbox(Translate("Threat Warning", "Tehdit Uyarısı"), &isDrawAlert);
    ImGui::TableNextColumn(); ImGui::Checkbox(Translate("Screen Warning", "Ekran Uyarısı"), &Alert);
    ImGui::TableNextColumn(); ImGui::Checkbox(Translate("Grenade Warning", "Bomba Uyarısı"), &Bomba);
    ImGui::TableNextColumn(); ImGui::Checkbox(Translate("Ipad View", "Ipad Görünümü"), &IpadModu);
	ImGui::EndTable();
}
ImGui::Separator();
if (ImGui::Button(Translate("Save Settings  ", "Ayarları Kaydet  "), ImVec2(170, 42))) { saveConfig(); }
ImGui::SameLine();
if (ImGui::Button(Translate("Load Settings  ", "Ayarları Yükle  "), ImVec2(170, 42))) { loadConfig(); }

ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), Translate("Key expiration date:", "Anahtar bitiş tarihi:"));
auto [days, hours, minutes, seconds] = calculateRemainingTime(EXP);
std::string countdown = std::to_string(days) + "day " +
                            std::to_string(hours) + "hours " +
                            std::to_string(minutes) + "minutes " +
                            std::to_string(seconds) + "second ";
ImGui::TextColored(ImColor(66, 139, 255, 255), countdown.c_str());	
ImGui::Separator();

}

if (espTab == 2) {

    ImGui::Spacing();
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.85f, 0.45f, 0.22f, 1.0f)); 
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.98f, 0.26f, 0.0f, 1.0f)); 

	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), Translate("ESP distance adjustment:", "ESP mesafe ayarı:"));
	ImGui::Separator();
  	ImGui::SliderFloat(Translate("Loot Crate", "Loot Sandığı"), &LootBoxDist, 0, 300, "%.1f m");
	ImGui::Separator();
	ImGui::SliderFloat(Translate("Crate Items", "Sandık Itemleri"), &CrateItemsDist, 10, 50, "%.1f m");
	ImGui::Separator();
	ImGui::SliderFloat(Translate("Vehicle", "Araba"), &VehicleDist, 0, 400, "%.1f m");
	ImGui::Separator();
	ImGui::SliderFloat(Translate("Items", "Eşyalar"), &LootDist, 0, 250, "%.1f m");
	ImGui::Separator();
	
	ImGui::SliderFloat(Translate("Skeleton Size", "İskelet Boyutu"), &SkeletonSize, 1.0f, 3.0f);
    ImGui::Separator();
	ImGui::SliderFloat(Translate("Ipad View FOV", "Ipad Görüş Açısı"), &IpadModu2, 80, 120);
    ImGui::Separator();
	ImGui::Text(Translate("Esp Color", "Esp Renk"));
    ImGui::Checkbox(Translate("Visibility Check", "Görünürlük Kontrolü"), &enableVisCheck);

    ImGui::ColorEdit4(Translate("Visible Color", "Görünen Renk"), 
                      (float*)&visibleColor, 
                      ImGuiColorEditFlags_NoInputs);
    ImGui::SameLine();
    ImGui::ColorEdit4(Translate("Not Visible Color", "Görünmeyen Renk"), 
                      (float*)&notVisibleColor, 
                      ImGuiColorEditFlags_NoInputs);
  		  ImGui::ColorEdit4(Translate("Grenade Lines Color", "Bomba Çizgi Renk"), 
                      (float*)&GrenadeCol, 
                      ImGuiColorEditFlags_NoInputs);			  
	ImGui::Separator();				  
    ImGui::PopStyleColor(3);
}

		}
if (Settings::Tab == 2) {
ImGui::TextColored(ImVec4(0.98f, 0.80f, 0.26f, 1.0f), Translate("Aimbot Settings", "Aimbot Ayarları"));
ImGui::Separator();
ImGui::Spacing();

ImGui::Checkbox(Translate("Enable Aimbot", "Aimbot'u Etkinleştir"), &AimBot);
ImGui::SameLine();
ImGui::Checkbox(Translate("Magic Bullet", "Sihirli Mermi"), &isMagicBullet);
ImGui::Checkbox(Translate("Show Crosshair", "Sabit Nişangah"), &showCrosshair);
ImGui::SameLine();
ImGui::Checkbox(Translate("Sniper Mode", "Knt Modu"), &sniperMode);
ImGui::Separator();
ImGui::Spacing();

    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), Translate("Aimbot Parameters: (?)", "Aimbot Parametreleri: (?)"));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.85f, 0.45f, 0.22f, 1.0f)); 
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.98f, 0.26f, 0.0f, 1.0f)); 

ImGui::SliderFloat(Translate("Distance", "Mesafe"), &AimDist, 0, 150, "%.1f m");
ImGui::Checkbox(Translate("FOV", "FOV"), &AimFov);
if (AimFov){
ImGui::SliderFloat(Translate(" ", " "), &AimSize, 0, 280, "%.1f°");
ImGui::SameLine();
ImGui::ColorEdit4(Translate("", ""), (float*)&fovcol, ImGuiColorEditFlags_NoInputs);
}

if (showCrosshair){
ImGui::Separator();
ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), Translate("Crosshair Settings: (?)", "Nişangah Ayarları: (?)"));
ImGui::ColorEdit4(Translate("Color", "Renk"), (float*)&crosshairColor,ImGuiColorEditFlags_NoInputs);
ImGui::SliderFloat(Translate("Size","Boyut"), &crosshairSize, 5.0f, 75.0f);
ImGui::SliderFloat(Translate("recc","Boyut"), &Config.AimBot.Recc, 0.0f, 3.0f);
ImGui::SliderFloat(Translate("Thickness","Kalınlık"), &crosshairThickness, 1.0f, 4.0f);
}

ImGui::PopStyleColor(3);
ImGui::Separator();
ImGui::Spacing();


ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), Translate("Trigger Mode (?)", "Tetikleme Modu (?)"));   
const char* triggersAimbot[3];
triggersAimbot[0] = Translate("Shooting", "Ateş Etme");
triggersAimbot[1] = Translate("Scoping", "Nişan Alma");
triggersAimbot[2] = Translate("Any (Shooting / Scoping)", "Herhangi (Ateş / Nişan)");

ImGui::Combo("##TriggerAimbot", (int*)&Trigger, triggersAimbot, IM_ARRAYSIZE(triggersAimbot));

ImGui::Separator();
ImGui::Spacing();

ImGui::Text(Translate("Target Settings", "Hedef Ayarları"));
ImGui::Checkbox(Translate("Ignore Knocked", "Baygınları Yok Say"), &Knock);
ImGui::SameLine();
ImGui::Checkbox(Translate("Ignore Bots", "Botları Yok Say"), &Bots2);

ImGui::Spacing();
ImGui::Separator();
		}

if (Settings::Tab == 3) {
ImGui::Spacing();
for (auto& i : items_data) {
if (ImGui::CollapsingHeader(i["Category"].get<std::string>().c_str())) {
ImGui::Spacing(); 
if (ImGui::BeginTable(("table_" + i["Category"].get<std::string>()).c_str(), 3, 
ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
int column = 0;
for (auto& item : i["Items"]) {
if (column % 3 == 0) ImGui::TableNextRow();
ImGui::TableNextColumn();
ImGui::Checkbox(item["itemName"].get<std::string>().c_str(), 
 (bool*)&Items[item["itemId"].get<int>()]);
column++;}
ImGui::EndTable();}}}}

if (Settings::Tab == 4) {
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), Translate("Skin Settings", "Desen Ayarları"));
    ImGui::Separator();
    ImGui::Spacing();
  if (ImGui::BeginTable("##ModGun", 1, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner)) {
            ImGui::TableSetupColumn("SKIN MOD ENABLE", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("KILL-MESSAGE ENABLE", ImGuiTableColumnFlags_WidthStretch);           
            ImGui::TableHeadersRow();
            ImGui::TableNextColumn();        
                        ImGui::Checkbox(OBFUSCATE("Skin-Mod"), &ModSkinn);
                        ImGui::SameLine(); 
                        ImGui::Checkbox(OBFUSCATE("Kill-Message"), &KillMessage);
                        ImGui::SameLine();
                        ImGui::Checkbox(OBFUSCATE("DeadBox Skin"), &DeasBoxSkin);
                        ImGui::EndTable(); 
                }
                  if (ImGui::BeginTable("##ModGun", 3, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner)) {
            ImGui::TableSetupColumn("PLAYER ENABLE", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("WEAPON SKIN ENABLE", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("CAR SKIN ENABLE", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableHeadersRow();
            ImGui::TableNextColumn();        

			  ImGui::RadioButton(OBFUSCATE("PLAYER"), &MenuSkinSelecttt, 0);
              ImGui::TableNextColumn();    
              ImGui::RadioButton(OBFUSCATE("WEAPON"), &MenuSkinSelecttt, 1);
              ImGui::TableNextColumn(); 
              ImGui::RadioButton(OBFUSCATE("CAR"), &MenuSkinSelecttt, 2);
              ImGui::EndTable(); 
                }
                      
                  if (MenuSkinSelecttt == 0) {
                      suitandolayermenu = true;
                      
                      weaponskinmenu = false;
                            carskinmenu = false;
             
                      }
                      
                  if (MenuSkinSelecttt == 1) {
                      weaponskinmenu = true;
                      carskinmenu = false;
                      suitandolayermenu = false;
           
                      }
                          if (MenuSkinSelecttt == 2) {
                      carskinmenu = true; 
                      
                      suitandolayermenu = false;
                      
                      weaponskinmenu = false;
                      
           
                      }
                      if (ModSkinn){
                        if (suitandolayermenu) {
                            
                        preferences.Outfit = true;
                        preferences.Parachute = true;
                        preferences.Emote = true;
                        preferences.Helmett = true;
                        preferences.Bagg = true;
                        preferences.Face = true;
                        
                    if (ImGui::BeginTable("##ModGun", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner)) {
            ImGui::TableSetupColumn(" Xsuit Skin Name", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Edit Skin", ImGuiTableColumnFlags_WidthStretch);
          
            ImGui::TableHeadersRow();
            
            ImGui::TableNextColumn();
                                    ImGui::Text(OBFUSCATE("X-SUIT & SET SKIN"));
                                    ImGui::TableNextColumn();
                                
									const char* xsuity[] = { "NO SKIN", "Golden Pharaoh X-Suit", "Blood Raven X-Suit", "Poseidon X-Suit", "Avalanche X-suit", "Silvanus X-suit", "Iridescence X-suit", "Arcane Jester X-Suit", "Stygian Liege X-Suit", "Marmoris X-Suit",
  "Fiore X-Suit", "Fireman Suit", "Ryan Set", "Yellow Mummy Set", "White Mummy Set", 
  "Psychophage Set", "Godzilla Set", "Ghidorah Set", "Forest Elf Set", "Daryl Dixon Set", "Rick Grimes Set", "The Fool Set", "Black Shark Diving Suit", 
  "The Lover's Grace Set", "Isaiah Thomas Jersey", "Glacier Witch Set", "Blood Nightmare Set",  "Rising Sun Set", "Flame of Wrath Set", "Sahara Princess Set","Bape Set"};
  
	       ImGui::Combo("##xs", &preferences.Config.Skin.XSuits, xsuity, IM_ARRAYSIZE(xsuity));
                                
                    start = std::chrono::high_resolution_clock::now();
                    callFunction = true;
                    prevXSuits = preferences.Config.Skin.XSuits;
           
                    ImGui::TableNextColumn();
                    ImGui::Text(OBFUSCATE("BackPack SKIN "));
                    ImGui::TableNextColumn();;    
                    const char* bgg[] = { "NO SKIN", "Pharaoh Backpack", "Blood Raven Backpack", "The Fool BackPack", "Luminous Galaxy BackPack", "Poseidon BackPack", "GACKT MOONSAGA BackPack", "Godzilla BackPack","Frosty Snowglobe BackPack"};
                    ImGui::Combo("##Bag", &preferences.bag, bgg, IM_ARRAYSIZE(bgg));
                    
                    
                    ImGui::TableNextColumn();
                    ImGui::Text(OBFUSCATE("Helmets SKIN "));
                    ImGui::TableNextColumn();          
                    const char* hmm[] = { "NO SKIN", "Inferno Rider", "Scarlet Beast", "Glacier", "Gold and Silk", "Mutated", "Intergalactic", "Masked Psychic", "First Love ", "Atlantic Tech"};
                    ImGui::Combo("##Helmet", &preferences.helmet, hmm, IM_ARRAYSIZE(hmm));
                    
                    
                    
                    ImGui::TableNextColumn();
                    ImGui::Text(OBFUSCATE("Emote "));
                    ImGui::TableNextColumn();;                   
                    const char* emt[] = { "NO Emote", "Emote 1", "Emote 2", "Emote 3", "Emote 4", "Emote 5", "Emote 6", "Emote 7","Emote 8"};
                    ImGui::Combo("##emote", &ModEmote1, emt, IM_ARRAYSIZE(emt));
                    
                    ImGui::TableNextColumn();
                    ImGui::Text(OBFUSCATE("Parachute SKIN "));
                    ImGui::TableNextColumn();;                   
                    const char* prt[] = { "NO SKIN", "Pharaoh's Scarab Parachute", "Enigmatic Nomad Parachute", "Poseidon Parachute", "Paperfold Gambit Parachute", "Labyrinth Beast Parachute", "Flamewraith Parachute", "Mega Kitty Parachute","Mega Yeti Parachute",  "Endless Glory Parachute", "Magma Skull Parachute", "Aquatic Fury Parachute", "CyberGen: Zero Parachute", "Radiant Phoenix Adarna Parachute", "Will of Horus Parachute", "Anubian Magistrate Parachute"};
                    ImGui::Combo("##Parachute", &preferences.Config.Skin.Parachute, prt, IM_ARRAYSIZE(prt));
                    }
                ImGui::EndTable(); 
                }
            
                        }
                        if  (weaponskinmenu) {
                            preferences.AWM = true;
                            preferences.DP28 = true;
                            preferences.M249 = true;
                            preferences.UZI = true;
                            preferences.UMP = true;
                            preferences.TOMMY = true;
                            preferences.VECTOR = true;
                            preferences.BIZON = true;
                            preferences.PAN = true;
                            preferences.M416 = true;
                            preferences.AKM = true;
                            preferences.SCARL = true;
                            preferences.M762 = true;
                            preferences.GROZA = true;
                            preferences.AUG = true;
                            preferences.M16 = true;
                            preferences.ACE32 = true;
                            preferences.KAR98 = true;
                            preferences.M24 = true;
                            

                    if (ImGui::BeginTable("##ModGun", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner)) {
            ImGui::TableSetupColumn(" Weapon Skin Name", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Edit Skin", ImGuiTableColumnFlags_WidthStretch);
        
            ImGui::TableHeadersRow();
              ImGui::TableNextColumn();
                                    
                                    ImGui::Text(OBFUSCATE("M416 SKIN"));
                                    ImGui::TableNextColumn();
                                    const char* m416[] = { "NO SKIN", "Glacier - M416", "The Fool - M416","Wanderer - M416","Lizard Roar - M416","Call of the Wild - M416", "TechnoCore - M416", "Imperial Splendor - M416", "Silver Guru - M416","Tidal Embrace - M416 ", "Shinobi Kami - M416 "};
                                    ImGui::Combo("##m4", &preferences.Config.Skin.M416, m416, IM_ARRAYSIZE(m416));
                                    
                            
                                    ImGui::TableNextColumn();
                                    ImGui::Text(OBFUSCATE("AKM SKIN"));
                                    ImGui::TableNextColumn();
                                    const char* AKM[] = { "NO SKIN", "Glacier - AKM", "Desert Fossil - AKM","Jack-o'-lantern - AKM","Ghillie Dragon - AKM","Gold Pirate - AKM","Codebreaker - AKM","Wandering Tyrant - AKM", "Starsea Admiral - AKM","Bunny Munchkin - AKM","Decisive Day - AKM"};
                                    ImGui::Combo("##AKM", &preferences.Config.Skin.AKM, AKM, IM_ARRAYSIZE(AKM));
                                    
                                   
                                    ImGui::TableNextColumn();
                                    ImGui::Text(OBFUSCATE("SCAR-L SKIN"));
                                    ImGui::TableNextColumn();
                                    const char* scr[] = { "NO SKIN", "Water Blaster - SCAR-L", "Enchanted Pumpkin - SCAR-L","Operation Tomorrow - SCAR-L","Hextech Crystal - SCAR-L ","Thorn of Malice - SCAR-L","Bloodstained Nemesis - SCAR-L", "Folly's Clasp - SCAR-L "};
                                    ImGui::Combo("##scar", &preferences.Config.Skin.Scar, scr, IM_ARRAYSIZE(scr));
                                    
                    
                                    ImGui::TableNextColumn();
                                    ImGui::Text(OBFUSCATE("M762 SKIN"));
                                    ImGui::TableNextColumn();;
                                    const char* mya[] =  {"NO SKIN", "8-bit Unicorn - M762", "Concerto of Love - M762","Deadly Precision - M762",  "Stray Rebellion - M762","Starcore - M762","Messi Football Icon - M762","Noctum Sunder - M762"};
                                    ImGui::Combo("##M762", &preferences.Config.Skin.M762, mya, IM_ARRAYSIZE(mya));
                                    
                                    
                                    
                                    ImGui::TableNextColumn();
                                    ImGui::Text(OBFUSCATE("GROZA SKIN"));
                                    ImGui::TableNextColumn();
                                    const char* gyz[] =  {"NO SKIN", "Forest Raider - GROZA", "Eventide Aria - Groza","Ryomen Sukuna - GROZA","Splendid Battle - GROZA","River Styx - Groza","Pumpkin Carol - Groza"};
                                    ImGui::Combo("##GROZA", &preferences.Config.Skin.Groza, gyz, IM_ARRAYSIZE(gyz));
                                    
                                    
                                    
                                    ImGui::TableNextColumn();                               
                                    ImGui::Text(OBFUSCATE("AUG SKIN"));
                                    ImGui::TableNextColumn();
                                    const char* asd[] =  {"NO SKIN", "Wandering Circus - AUG","Evangelion 4th Angel - AUG","Forsaken Glace - AUG"};
                                    ImGui::Combo("##AUG", &preferences.Config.Skin.AUG, asd, IM_ARRAYSIZE(asd));
                                    
                                    
                                    ImGui::TableNextColumn();
                                    ImGui::Text(OBFUSCATE("M16A4 SKIN"));
                                    ImGui::TableNextColumn();
                                    const char* moa[] =  {"NO SKIN", "Blood & Bones - M16A4", "Aurora Pulse - M16A4","Radiant Edge - M16A4","Skeletal Core - M16A4","Dracoguard - M16A4"};
                                    ImGui::Combo("##M16A4", &preferences.Config.Skin.M16A4, moa, IM_ARRAYSIZE(moa));
                                    
                                    
                                    ImGui::TableNextColumn();
                                    ImGui::Text(OBFUSCATE("ACE32 SKIN "));
                                    ImGui::TableNextColumn();
                                    const char* acs[] =  {"NO SKIN", "Beam Blast - ACE32 ","Icicle Spike - ACE32"};
                                    ImGui::Combo("##ACE", &preferences.Config.Skin.ACE32, acs, IM_ARRAYSIZE(acs));            
                                    
                                    
                                    
                                    ImGui::TableNextColumn();
                                    ImGui::Text(OBFUSCATE("KAR98K SKIN"));
                                    ImGui::TableNextColumn();
                                    const char* lkh[] =  {"NO SKIN", "Terror Fang - Kar98K", "Kukulkan Fury - Kar98K","Moonlit Grace - Kar98K","Titanium Shark - Kar98K","Nebula Hunter - Kar98K","Violet Volt - Kar98K"};
                                    ImGui::Combo("##KAR98K", &preferences.Config.Skin.K98, lkh, IM_ARRAYSIZE(lkh));
                                    
                                    
                                    
                                    ImGui::TableNextColumn();
                                    ImGui::Text(OBFUSCATE("M24 SKIN"));
                                    ImGui::TableNextColumn();
                                    const char* myd[] =  {"NO SKIN", "The Seven Seas - M24", "Pharaoh's Might - M24","Lady Butterfly - M24","Circle of Life - M24","Cadence Maestro - M24"};
                                    ImGui::Combo("##M24", &preferences.Config.Skin.M24, myd, IM_ARRAYSIZE(myd));
                                    
                                    
                                    
                                    ImGui::TableNextColumn();
                                    ImGui::Text(OBFUSCATE("AWM SKIN"));
                                    ImGui::TableNextColumn();
                                    const char* ahy[] =  {"NO SKIN", "Mauve Avenger - AWM", "Field Commander - AWM","Godzilla - AWM","Rainbow Drake - AWM","Flamewave - AWM"};
                                    ImGui::Combo("##AWM", &preferences.Config.Skin.AWM, ahy, IM_ARRAYSIZE(ahy));
                                    
                                    
                                    
                                    ImGui::TableNextColumn();      
                                    ImGui::Text(OBFUSCATE("DP28 SKIN"));
                                    ImGui::TableNextColumn();
                                    const char* dpp[] =  {"NO SKIN", "Enigmatic Hunter - DP28", "Gilded Jade Dragon - DP28","Nautical Warrior - DP-28","Shenron - DP-28"};
                                    ImGui::Combo("##DP", &preferences.Config.Skin.DP28, dpp, IM_ARRAYSIZE(dpp));
                                    
                                    
                                    
                                    ImGui::TableNextColumn();
                                    ImGui::Text(OBFUSCATE("M249 SKIN"));
                                    ImGui::TableNextColumn();
                                    const char* mkk[] =  {"NO SKIN", "Winter Queen - M249", "Party Parcel - M249 V","Moondrop Eterna - M249","Stargaze Fury - M249"};
                                    ImGui::Combo("##M249", &preferences.Config.Skin.M249, mkk, IM_ARRAYSIZE(mkk));
                                    
                                    
                                    
                                    ImGui::TableNextColumn();
                                    ImGui::Text(OBFUSCATE("UZI SKIN"));
                                    ImGui::TableNextColumn();
                                    const char* uzy[] = { "NO SKIN", "Savagery - UZI", "Ethereal Emblem - UZI","Romantic Moments - UZI","Shimmer Power - UZI","Mystech - UZI","Juicer - UZI"};
                                    ImGui::Combo("##UZI", &preferences.Config.Skin.UZI, uzy, IM_ARRAYSIZE(uzy));
                                    
                                    
                                    
                                    
                                    ImGui::TableNextColumn();
                                    ImGui::Text(OBFUSCATE("UMP SKIN"));
                                    ImGui::TableNextColumn();
                                    const char* umy[] = { "NO SKIN", "Dragonfire - UMP45", "Outlawed Fantasy - UMP45","8-Bit Blast - UMP45","Rainbow Stinger - UMP45","Marine Evolution - UMP45","Carnival Waves - UMP45","Cryofrost Shard - UMP45"};
                                    ImGui::Combo("##UMP", &preferences.Config.Skin.UMP, umy, IM_ARRAYSIZE(umy));
                                    
                                    
                                    
                                    
                                    ImGui::TableNextColumn();
                                    ImGui::Text(OBFUSCATE("Thompson SKIN "));
                                    ImGui::TableNextColumn();
                                    const char* tho[] =  {"NO SKIN", "Candy Cane - Thompson","Steampunk - Thompson "};
                                    ImGui::Combo("##Thompson", &preferences.Config.Skin.Thompson, tho, IM_ARRAYSIZE(tho));            
                                    
                                    
                                    
                                    
                                    ImGui::TableNextColumn();
                                    ImGui::Text(OBFUSCATE("BIZON SKIN"));
                                    ImGui::TableNextColumn();
                                    const char* bzy[] =  {"NO SKIN", "Blazing Chameleon - PP-19 Bizon", "Skullcrusher - PP-19 Bizon","Soldier Soul - PP-19 Bizon"};
                                    ImGui::Combo("##BIZON", &preferences.Config.Skin.Bizon, bzy, IM_ARRAYSIZE(bzy));
                                    
                                    
                                    
                                    
                                    ImGui::TableNextColumn();
                                    ImGui::Text(OBFUSCATE("PAN SKIN"));
                                    ImGui::TableNextColumn();
                                    const char* pnh[] = { "NO SKIN", "Glacier - PAN", "Night of Rock - PAN","Crocodile - PAN","Accolade - PAN","Break Pad - PAN","Chicken Hot - PAN","Faerie Luster - PAN","Anniversary - PAN","Olive Branch - PAN"};
                                    ImGui::Combo("##Pan", &preferences.Config.Skin.Pan, pnh, IM_ARRAYSIZE(pnh));
                                    }
                    ImGui::EndTable(); 
                        }
                        
                        
                        
                        if (carskinmenu) {
                            preferences.Boat = true;
                            preferences.MiniBus = true;
                            preferences.Buggy = true;
                            preferences.Mirado = true;
                            preferences.BigFoot = true;
                            preferences.Moto = true;
                            preferences.UAZ = true;
                            preferences.CoupeRB = true;
                            preferences.Dacia = true;
                            
                            
           if (ImGui::BeginTable("##ModGun", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner)) {
            ImGui::TableSetupColumn(" Car Skin Name", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Edit Skin", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableHeadersRow();
            ImGui::TableNextColumn();
                    
                    
                    ImGui::Text(OBFUSCATE("DACIA SKIN"));
                                    ImGui::TableNextColumn();
                                    const char* pou[] = { "NO SKIN", "Koenigsegg Gemera (Dawn) ", "Lamborghini Estoque Oro ","Tesla Roadster (Diamond) ","Pumpkin Dacia ","Castle Dacia", "Speedy Reindeer Dacia ", "Zombie Mess Dacia", "Dodge Charger SRT Hellcat - Fuchsia","Dodge Charger SRT Hellcat - Tuscan Torque ", "Dodge Charger SRT Hellcat Jailbreak - Violet Venom  ","Koenigsegg Gemera (Silver Gray) ","Koenigsegg Gemera (Rainbow) ","Tesla Roadster (Amethyst) ","Tesla Roadster (Digital Water) ","Lamborghini Estoque Metal Grey ","Dodge Charger SRT Hellcat - Tuscan Torque ","Dodge Charger SRT Hellcat Jailbreak - Violet Venom ","Ghost Rosa ","Ghost Violet ","Ghost Gleam ","Midknight Dacia (Lv. 4) "};
                                    ImGui::Combo("##dac", &preferences.Config.Skin.Dacia, pou, IM_ARRAYSIZE(pou));
                                    
                                    
                                    
                                  
                                    ImGui::TableNextColumn();
                                    ImGui::Text(OBFUSCATE("Coupe RB SKIN "));
                                    ImGui::TableNextColumn();
                                    const char* cou[] =  {"NO SKIN", "Lamborghini Aventador SVJ Blue ","Bugatti La Voiture Noire (Nebula) ","Warp Dawn ","Koenigsegg Jesko (Dawn) ","McLaren 570S (Zenith Black) ","McLaren 570S (Lunar White) ","Aston Martin Valkyrie (Racing Green) ","Aston Martin Valkyrie (Luminous Diamond) ","McLaren 570S (Raspberry) ","McLaren 570S (Glory White) ","McLaren 570S (Royal Black) ","McLaren 570S (Pearlescent) ","Koenigsegg Jesko (Silver Gray) ","Koenigsegg Jesko (Rainbow) ","Lamborghini Aventador SVJ Verde Alceo ","Lamborghini Centenario Galassia ","Lamborghini Centenario Carbon Fiber ","Koenigsegg One:1 Gilt ","Koenigsegg One:1 Cyber Nebula ","Koenigsegg One:1 Jade ","Koenigsegg One:1 Phoenix ","Warp Green ","Warp Universe ","Dodge Challenger SRT Hellcat - Blaze ","Dodge Challenger SRT Hellcat - Lime ","Maserati MC20 Bianco Audace ","Maserati MC20 Rosso Vincente ","Maserati MC20 Sogni ","Bugatti Veyron 16.4 (Shining) ","Bugatti Veyron 16.4 (Gold) ","Bugatti Veyron 16.4 ","Bugatti La Voiture Noire ","Bugatti La Voiture Noire (Alloy) ","Bugatti La Voiture Noire (Warrior) ","Dodge Challenger SRT Hellcat Jailbreak - Hellfire ","Pagani Zonda R (Tricolore Carbon) ","Pagani Zonda R (Bianco Benny) ","Pagani Zonda R (Melodic Midnight) ","Pagani Imola (Grigio Montecarlo) ","Pagani Imola (Crystal Clear Carbon) ","Pagani Imola (Nebula Dream) ","Pagani Imola (Arctic Aegis)"};
                                    ImGui::Combo("##Coupe", &preferences.Config.Skin.CoupeRP, cou, IM_ARRAYSIZE(cou)); 
                                    
                                    
                                    
                                    ImGui::TableNextColumn();
                                    ImGui::Text(OBFUSCATE("UAZ SKIN "));
                                    ImGui::TableNextColumn();
                                    const char* uazz[] =  {"NO SKIN", "Lamborghini Urus Giallo Inti","Cute Kitten UAZ ","Godzilla UAZ (Lv. 3) ","Robust Wild ","Lamborghini Urus Pink ","Maserati Levante Blu Emozione ","Maserati Luce Arancione ","Maserati Levante Neon Urbano ","Maserati Levante Firmamento ","Aston Martin DBX707 (Neon Purple) ","Aston Martin DBX707 (Quasar Blue) ","Dodge Hornet - Scarlet Sting ","Dodge Hornet GLH Concept - Redline ","Dodge Hornet - Sunburst ","Dodge Hornet GLH Concept - Redline ","Dodge Hornet - Sunburst ","Armed UAZ "};                                                                       
                                    ImGui::Combo("##uaz", &preferences.Config.Skin.UAZ, uazz, IM_ARRAYSIZE(uazz));
                                    
                                    
                                    ImGui::TableNextColumn();   
                                    ImGui::Text(OBFUSCATE("MotoBike"));
                                    ImGui::TableNextColumn();
                                    const char* motoo[] =  {"NO SKIN", "DUCATI Panigale V4S","Ducati Panigale V4S Black Phantom ","Ducati Panigale V4S Crimson Storm ","Phantom Motorcycle (Lv. 7) ","LINE FRIENDS Lovey Dovey 2-Seat Motorcycle (Lv. 4) ","Ducati Panigale V4S Swift Mirage ","Roaring Tiger Motorcycle (Lv. 3) ","Skeleton Chariot (Lv. 3) "};  
                                        
                                    ImGui::Combo("##moto", &preferences.Config.Skin.Moto, motoo, IM_ARRAYSIZE(motoo)); 
                                    
                                    
                                    
                                    
                                    
                                    ImGui::TableNextColumn();   
                                    ImGui::Text(OBFUSCATE("Boat SKIN"));
                                    ImGui::TableNextColumn();
                                    const char* foot[] =  {"NO SKIN", "Imperial Gold Speedboat ","Lifesaver Speedboat ","Chicken Speedboat ","Hungry Shark Speedboat ","The Seven Seas Speedboat ","Neko Sakura Speedboat ","Pineapple Speedboat ","Cute Penguin Speedboat ","Armored Carrier ","Kong Team Speedboat "};  
                                        
                                    ImGui::Combo("##Bigfoot", &preferences.Config.Skin.Boat, foot, IM_ARRAYSIZE(foot)); 
                                    
                                    
                                    
                                    ImGui::TableNextColumn();   
                                    ImGui::Text(OBFUSCATE("Mirado SKIN"));
                                    ImGui::TableNextColumn();
                                    const char* rado[] =  {"NO SKIN","Armored Hunter Mirado "};  
                                        
                                    ImGui::Combo("##OMirado", &preferences.Config.Skin.Mirado, rado, IM_ARRAYSIZE(rado)); 
                                                          
                                    
                                    ImGui::TableNextColumn();   
                                    ImGui::Text(OBFUSCATE("Buggy SKIN"));
                                    ImGui::TableNextColumn();
                                    const char* uggy[] =  {"NO SKIN","Ceratops Blitz Buggy (Lv. 4) ","Ancient Guardian Buggy  ","Bowknot Buggy ","Lifesaver Buggy ","Black Magma Buggy ","Naughty Christmas Buggy ","Off-road Buggy ","Street Art Buggy "};                                     
                                    ImGui::Combo("##Buggy", &preferences.Config.Skin.Buggy, uggy, IM_ARRAYSIZE(uggy)); 
                                    
                                                     
                                    ImGui::TableNextColumn();   
                                    ImGui::Text(OBFUSCATE("MiniBus SKIN"));
                                    ImGui::TableNextColumn();
                                    const char* mini[] =  {"NO SKIN","Winning Chicken Bus ","Tsunami Bus ","Wrestling Bus ","Cartoon Chicken Bus ","Roaring Grizzly Bus ","Ice Cream Bus "};  
                                        
                                    ImGui::Combo("##miniB", &preferences.Config.Skin.MiniBus, mini, IM_ARRAYSIZE(mini));
                                    
                                     
                                      
                                    
                                       
                                    ImGui::TableNextColumn();   
                                    ImGui::Text(OBFUSCATE("Monster Truck SKIN"));
                                    ImGui::TableNextColumn();
                                    const char* bgyuz[] =  {"NO SKIN","Jovial Tread Monster Truck "};  
                                        
                                    ImGui::Combo("##bg77", &preferences.Config.Skin.Bigfoot, bgyuz, IM_ARRAYSIZE(bgyuz));                                               
                        ImGui::EndTable(); 
                        }}
						}
ImGui::EndChild();
}
ImGui::End();
ImGui::Render();
ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
return orig_eglSwapBuffers(dpy, surface);
}
/////touch input
int (*original_AInputQueue_getEvent)(AInputQueue*, AInputEvent**);
int hooked_AInputQueue_getEvent(AInputQueue* queue, AInputEvent** event) {
int result = original_AInputQueue_getEvent(queue, event);
if (result >= 0 && *event) {
int32_t type = AInputEvent_getType(*event);
if (type == AINPUT_EVENT_TYPE_MOTION) {
int32_t action = AMotionEvent_getAction(*event) & AMOTION_EVENT_ACTION_MASK;
int32_t pointerIndex = (AMotionEvent_getAction(*event) & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) 
>> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
float rawX = AMotionEvent_getX(*event, pointerIndex);
float rawY = AMotionEvent_getY(*event, pointerIndex);
float scaledX = (rawX * glWidth) / screenWidth;
float scaledY = (rawY * glHeight) / screenHeight;
ImGuiIO& io = ImGui::GetIO();
switch (action) {
case AMOTION_EVENT_ACTION_DOWN:
case AMOTION_EVENT_ACTION_POINTER_DOWN:
io.MousePos = ImVec2(scaledX, scaledY);
io.MouseDown[0] = true;
break;
case AMOTION_EVENT_ACTION_UP:
case AMOTION_EVENT_ACTION_POINTER_UP:
io.MousePos = ImVec2(scaledX, scaledY);
io.MouseDown[0] = false;
break;
case AMOTION_EVENT_ACTION_MOVE:
io.MousePos = ImVec2(scaledX, scaledY);
break;
default:
break;}}}
return result;}

void *(*oProcessEvent)(UObject *pObj, UFunction *pFunc, void *pArgs);
void *hkProcessEvent(UObject *pObj, UFunction *pFunc, void *pArgs) {
  if (pFunc) {
        if (pFunc->GetFullName() == "Function Engine.HUD.ReceiveDrawHUD") {
            AHUD *pHUD = (AHUD *)pObj;
            if (pHUD) {
                auto Params = (AHUD_ReceiveDrawHUD_Params *)pArgs;
                if (Params) {
                    RenderESP(pHUD, Params->SizeX, Params->SizeY);
                }
            }
        }
    }
    
     if (DeasBoxSkin) {
    if( std::string(pObj->GetName().c_str()).find("DeadBoxAvatarComponent") != std::string::npos ) {
   UDeadBoxAvatarComponent *DeadBoxPointer = ( UDeadBoxAvatarComponent *) pObj; 
    if( std::string(pFunc->GetFullName().c_str()).find("GetLuaFilePath") != std::string::npos ) {
    uint32_t Key = DeadBoxPointer->IsSelf();              
    auto GWorld = GetWorld();
    if (GWorld){
        if (GWorld->NetDriver->ServerConnection)
            if(GWorld->NetDriver->ServerConnection->PlayerController){
    ASTExtraPlayerController *g_LocalController = (ASTExtraPlayerController *)GWorld->NetDriver->ServerConnection->PlayerController;
    ASTExtraPlayerCharacter *g_LocalPlayer = (ASTExtraPlayerCharacter *)g_LocalController->AcknowledgedPawn;
                if(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated){
if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "M416")){        
if (preferences.M416 == 1) 
DeadBoxPointer->ChangeItemAvatar(new_Skin.M416_1, true); //Glacier - M416 

}
if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "AKM")){
if (preferences.AKM == 1)
DeadBoxPointer->ChangeItemAvatar( new_Skin.AKM, true); //Sculpture - AKM
}
if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "SCAR")){
if (preferences.SCARL == 1)
DeadBoxPointer->ChangeItemAvatar( new_Skin.Scar, true); //Sculpture - AKM

}
if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "M762")){
if (preferences.M762 == 1)
DeadBoxPointer->ChangeItemAvatar( new_Skin.M762, true); //Sculpture - AKM

}
if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "GROZA")){
if (preferences.GROZA == 1)
DeadBoxPointer->ChangeItemAvatar( new_Skin.Groza, true); //Sculpture - AKM

}
if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "UZI")){
if (preferences.UZI == 1)
DeadBoxPointer->ChangeItemAvatar( new_Skin.UZI, true); //Sculpture - AKM

}
if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "M16A4")){
if (preferences.M16 == 1)
DeadBoxPointer->ChangeItemAvatar( new_Skin.M16A4, true); //Sculpture - AKM

}
if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "UMP45")){
if (preferences.UMP == 1)
DeadBoxPointer->ChangeItemAvatar( new_Skin.UMP, true); //Sculpture - AKM

}
if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "ACE32")){
if (preferences.ACE32 == 1)
DeadBoxPointer->ChangeItemAvatar( new_Skin.ACE32, true); //Sculpture - AKM

}
if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "AWM")){
if (preferences.AWM == 1)
DeadBoxPointer->ChangeItemAvatar( new_Skin.AWM, true); //Sculpture - AKM

}
if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "M24")){
if (preferences.M24 == 1)
DeadBoxPointer->ChangeItemAvatar( new_Skin.M24, true); //Sculpture - AKM

}

if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "AWM")){
if (preferences.M249 == 1)
DeadBoxPointer->ChangeItemAvatar( new_Skin.M249, true); //Sculpture - AKM

}
if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "DP28")){
if (preferences.DP28 == 1)
DeadBoxPointer->ChangeItemAvatar( new_Skin.DP28, true); //Sculpture - AKM

}

if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "AUG")){
if (preferences.AUG == 1)
DeadBoxPointer->ChangeItemAvatar( new_Skin.AUG, true); //Sculpture - AKM
}

if(strstr(g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponName().ToString(), "KAR")){
if (preferences.KAR98 == 1)
DeadBoxPointer->ChangeItemAvatar( new_Skin.K98, true); //Sculpture - AKM

}}}}}}}
    return oProcessEvent(pObj, pFunc, pArgs);
}
///////load hack
void *monster_thread(void *) { 
UE4 = Tools::GetBaseAddress("libUE4.so"); 
while (!UE4) {
UE4 = Tools::GetBaseAddress("libUE4.so");
sleep(1);}
while (!g_App){
g_App = *(android_app **) (UE4 + Gapp_offset);
sleep(1);}
LOGI("libUE4.so: %p", UE4);	
FName::GNames = GetGNames();
while (!FName::GNames) {
FName::GNames = GetGNames();
sleep(1);} 
UObject::GUObjectArray = (FUObjectArray *) (UE4 + GUObjectArray_offset); 
CanaryBlock1(); CanaryBlock2(); CanaryBlock3(); CanaryBlock4();
HOOK_LIB("libUE4.so", "0xCA94C50", hooked_AInputQueue_getEvent, original_AInputQueue_getEvent);//*/
HOOK_LIB("libUE4.so", "0xCA96180", _eglSwapBuffers, orig_eglSwapBuffers);//*/
A64HookFunction(reinterpret_cast<void *>(UE4 + 0x843ec24), reinterpret_cast<void *>(hkProcessEvent), reinterpret_cast<void **>(&oProcessEvent));

items_data = json::parse(JSON_ITEMS);
rifle1 = json::parse(Rifle);
sub1 = json::parse(Sub);    
sniper1 = json::parse(Sniper);      
scope1 = json::parse(Scope);
mag1 = json::parse(Mag);    
ammo1 = json::parse(Ammo);  
atta1 = json::parse(Atta);
armor1 = json::parse(Armor);    
medic1 = json::parse(Medic);    
grenade1 = json::parse(Grenade);    
special1 = json::parse(Special); 
return NULL;}
#include "engine/login.h"
