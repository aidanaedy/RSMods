#include "Main.h"

#if defined _DEBUG
bool debug = true;
#else
bool debug = false;
#endif


unsigned WINAPI EnumerationThread(void*) {
	while (!GameLoaded) // We are in no hurry :)
		Sleep(5000);

	Settings.ReadKeyBinds();
	Settings.ReadModSettings();

	int oldDLCCount = Enumeration.GetCurrentDLCCount(), newDLCCount = oldDLCCount;

	while (true) {
		if (Settings.ReturnSettingValue("ForceReEnumerationEnabled") == "automatic") {
			oldDLCCount = newDLCCount;
			newDLCCount = Enumeration.GetCurrentDLCCount();

			if (oldDLCCount != newDLCCount)
				Enumeration.ForceEnumeration();
		}

		Sleep(Settings.GetModSetting("CheckForNewSongsInterval"));
		//Sleep(EnumSliderVal);
	}

	return 0;
}

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM keyPressed, LPARAM lParam) {
	if (menuEnabled && ImGui_ImplWin32_WndProcHandler(hWnd, msg, keyPressed, lParam)) {
		//if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONDBLCLK || msg == WM_LBUTTONUP)
		//	return true;

		return true;
	}

	if (msg == WM_KEYUP) {
		/*
		if (keyPressed == VK_DELETE) {
			float volume;
			RTPCValue_type type;

			SetRTPCValue("Mixer_Music", (float)volume, 0xffffffff, 0, AkCurveInterpolation_Linear);
			GetRTPCValue("Mixer_Music", 0xffffffff, &volume, &type);
			std::cout << volume << std::endl;
		}
		*/

		if (GameLoaded) {
			if (keyPressed == Settings.GetKeyBind("ToggleLoftKey") && Settings.ReturnSettingValue("ToggleLoftEnabled") == "on") { // Game must not be on the startup videos or it will crash
				MemHelpers.ToggleLoft();
				std::cout << "Toggle Loft" << std::endl;
			}

			else if (keyPressed == Settings.GetKeyBind("AddVolumeKey") && Settings.ReturnSettingValue("AddVolumeEnabled") == "on") {
				//MemHelpers.AddVolume(5); TODO: find out how to use Set/GetRTPCValue to change volume
				std::cout << "Adding 5 Volume" << std::endl;
			}

			else if (keyPressed == Settings.GetKeyBind("DecreaseVolumeKey") && Settings.ReturnSettingValue("DecreaseVolumeEnabled") == "on") {
				//MemHelpers.DecreaseVolume(5);
				std::cout << "Subtracting 5 Volume" << std::endl;
			}

			else if (keyPressed == Settings.GetKeyBind("ShowSongTimerKey") && Settings.ReturnSettingValue("ShowSongTimerEnabled") == "on") {
				MemHelpers.ShowSongTimer();
				std::cout << "Show Me Dat Timer Bruh" << std::endl;
			}

			else if (keyPressed == Settings.GetKeyBind("ForceReEnumerationKey") && Settings.ReturnSettingValue("ForceReEnumerationEnabled") == "manual") {
				Enumeration.ForceEnumeration();
				std::cout << "ENUMERATE YOU FRICKIN' SOAB" << std::endl;
			}

			else if (keyPressed == Settings.GetKeyBind("RainbowStringsKey") && Settings.ReturnSettingValue("RainbowStringsEnabled") == "on") {
				ERMode.ToggleRainbowMode();
				std::cout << "Rainbows Are Pretty Cool" << std::endl;
			}
		}

		if (debug) {
			if (keyPressed == VK_INSERT)
				menuEnabled = !menuEnabled;
		}
	}

	return CallWindowProc(oWndProc, hWnd, msg, keyPressed, lParam);
}

void SetCustomColors() {
	RSColor iniColor;

	for (int strIdx = 0; strIdx < 6;strIdx++) {
		iniColor = Settings.GetCustomColors(true)[strIdx];
		int H;
		float S, L;
		CollectColors.RGB2HSL(iniColor.r, iniColor.g, iniColor.b, H, S, L);

		std::map<std::string, RSColor> customColors = {
			{"Ambient", CollectColors.GetAmbientStringColor(H, true)},
			{"Disabled", CollectColors.GetDisabledStringColor(H, S, L, true)},
			{"Enabled", iniColor},
			{"Glow", CollectColors.GetGlowStringColor(H)},
			{"PegsTuning", CollectColors.GetGlowStringColor(H)},
			{"PegsReset", CollectColors.GetPegResetColor()},
			{"PegsSuccess", CollectColors.GetPegSuccessColor(true)},
			{"PegsInTune", CollectColors.GetPegInTuneColor(H, true)},
			{"PegsOutTune", CollectColors.GetPegOutTuneColor()},
			{"TextIndicator", CollectColors.GetRegTextIndicatorColor(H, true)},
			{"ForkParticles", CollectColors.GetRegForkParticlesColor(H, true)},
			{"NotewayNormal", CollectColors.GetNotewayNormalColor(H, S, L, true)},
			{"NotewayAccent", CollectColors.GetNotewayAccentColor(H, true)},
			{"NotewayPreview", CollectColors.GetNotewayPreviewColor(H, true)},
			{"GC_Main", CollectColors.GetGuitarcadeMainColor(H, strIdx, true)},
			{"GC_Add", CollectColors.GetGuitarcadeAdditiveColor(H, strIdx, true)},
			{"GC_UI", CollectColors.GetGuitarcadeUIColor(H, strIdx, true)}
		};

		ERMode.SetCustomColors(strIdx, customColors);
	}
}

void GenerateTexture(IDirect3DDevice9* pDevice) {
	while (GetModuleHandleA("gdiplus.dll") == NULL) //JIC, to prevent crashing
		Sleep(500);

	using namespace Gdiplus;
	UINT width = 256, height = 128;
	int lineHeight = 8;

	if (Ok != GdiplusStartup(&token_, &inp, NULL))
		std::cout << "GDI+ failed to start up!" << std::endl;

	Bitmap bmp(width, height, PixelFormat32bppARGB);
	Graphics graphics(&bmp);

	REAL blendPositions[] = { 0.0f, 0.4f, 1.0f };

	for (int i = 0; i < 16;i++) {
		RSColor iniColor = Settings.GetCustomColors(i % 8)[i % 8]; // If we are in range of 0-7, grab the normal colors, otherwise grab CB colors
		Gdiplus::Color middleColor(iniColor.r * 255, iniColor.g * 255, iniColor.b * 255);

		Gdiplus::Color gradientColors[] = { Gdiplus::Color::Black, middleColor , Gdiplus::Color::White };
		LinearGradientBrush linGrBrush( // Base texture for note gradients (top / normal)
			Point(0, 0),
			Point(width, lineHeight),
			Gdiplus::Color::Black,
			Gdiplus::Color::White);
		LinearGradientBrush whiteCoverupBrush( // Coverup for some spotty gradients (top / normal)
			Point(width - 3, lineHeight * 5),
			Point(width, height),
			Gdiplus::Color::White,
			Gdiplus::Color::White);

		linGrBrush.SetInterpolationColors(gradientColors, blendPositions, 3);
		graphics.FillRectangle(&linGrBrush, 0, i * lineHeight, width, lineHeight);
		graphics.FillRectangle(&whiteCoverupBrush, width - 3, i * lineHeight, width, lineHeight); // Don't hate me for this hacky fix to the black bars.
	}

	// Uncomment if you want to save the generated texture
	/*CLSID pngClsid;
	CLSIDFromString(L"{557CF406-1A04-11D3-9A73-000F81EF32E}", &pngClsid); //for BMP: {557cf400-1a04-11d3-9a73-0000f81ef32e}
	bmp.Save(L"generatedTexture.png", &pngClsid); */

	BitmapData bitmapData;
	D3DLOCKED_RECT lockedRect;

	D3DXCreateTexture(pDevice, width, height, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &ourTexture);
	ourTexture->LockRect(0, &lockedRect, 0, 0);

	bmp.LockBits(&Rect(0, 0, width, height), ImageLockModeRead, PixelFormat32bppARGB, &bitmapData);
	unsigned char* pSourcePixels = (unsigned char*)bitmapData.Scan0;
	unsigned char* pDestPixels = (unsigned char*)lockedRect.pBits;

	for (int y = 0; y < height; ++y)
	{
		// copy a row
		memcpy(pDestPixels, pSourcePixels, width * 4);   // 4 bytes per pixel

		// advance row pointers
		pSourcePixels += bitmapData.Stride;
		pDestPixels += lockedRect.Pitch;
	}

	ourTexture->UnlockRect(0);

	//D3DXSaveTextureToFileA("generatedTexture_d3d.dds", D3DXIFF_DDS, ourTexture, 0);

	SetCustomColors();
}

HRESULT __stdcall Hook_EndScene(IDirect3DDevice9* pDevice) {
	HRESULT hRet = oEndScene(pDevice);
	DWORD dwReturnAddress = (DWORD)_ReturnAddress(); //EndScene is called both by the game and by Steam's overlay renderer, and there's no need to draw our stuff twice

	if (dwReturnAddress > Offsets.baseEnd)
		return hRet;

	static bool init = false; // Has this been ran before (AKA run only once, at startup)

	if (!init) {
		init = true;

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImFont* font = io.Fonts->AddFontFromMemoryCompressedTTF(RobotoFont_data, RobotoFont_size, 20);

		D3DDEVICE_CREATION_PARAMETERS d3dcp;
		pDevice->GetCreationParameters(&d3dcp);
		hThisWnd = d3dcp.hFocusWindow;

		oWndProc = (WNDPROC)SetWindowLongPtr(hThisWnd, GWLP_WNDPROC, (LONG_PTR)WndProc);

		ImGui_ImplWin32_Init(hThisWnd);
		ImGui_ImplDX9_Init(pDevice);
		ImGui::GetIO().ImeWindowHandle = hThisWnd;
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

		GenerateTexture(pDevice, &Red, D3DCOLOR_ARGB(255, 000, 255, 255));
		GenerateTexture(pDevice, &Green, D3DCOLOR_ARGB(255, 0, 255, 0));
		GenerateTexture(pDevice, &Blue, D3DCOLOR_ARGB(255, 0, 0, 255));
		GenerateTexture(pDevice, &Yellow, D3DCOLOR_ARGB(255, 255, 255, 0));

		D3DXCreateTextureFromFile(pDevice, L"notes_gradient_normal.dds", &gradientTextureNormal); //if those don't exist, note heads will be "invisible" | 6-String Model
		D3DXCreateTextureFromFile(pDevice, L"notes_gradient_seven.dds", &gradientTextureSeven); // 7-String Note Colors 
		D3DXCreateTextureFromFile(pDevice, L"doesntexist.dds", &nonexistentTexture); // Black Notes
		D3DXCreateTextureFromFile(pDevice, L"gradient_map_additive.dds", &additiveNoteTexture); // Note Stems

		for (int i = 0; i < 12;i++)
			GuitarSpeakStartingTexts.push_back("No value set!");

		std::cout << "ImGUI Init" << std::endl;

		GenerateTexture(pDevice);
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	if (menuEnabled) {
		ImGui::Begin("RS Modz");
		/*
		ImGui::SliderInt("Enumeration Interval", &EnumSliderVal, 100, 100000);
		ImGui::InputInt("Curr Slide", &currStride);
		ImGui::InputInt("Curr PrimCount", &currPrimCount);
		ImGui::InputInt("Curr NumVertices", &currNumVertices);
		ImGui::InputInt("Curr StartIndex", &currStartIndex);
		ImGui::InputInt("Curr StarRegister", &currStartRegister);
		ImGui::InputInt("Curr PrimType", &currPrimType);
		ImGui::InputInt("Curr DeclType", &currDeclType);
		ImGui::InputInt("Curr VectorCount", &currVectorCount);
		ImGui::InputInt("Curr NumElements", &currNumElements);
		ImGui::InputInt("Curr Idx", &currIdx);

		if (enableColorBlindCheckboxGUI)
			ImGui::Checkbox("Colorblind Mode", &cbEnabled);

		if (ImGui::Button("Add"))
			if (allMeshes.size() > 0)
				removedMeshes.push_back(allMeshes[currIdx]);

		ImGui::End();

		ImGui::Begin("LOOSE CANNONS");
		ImGui::ListBoxHeader("Removed models");
		counter = 0;
		for (auto mesh : removedMeshes) {
			if (ImGui::Selectable(mesh.ToString().c_str(), false))
				selectedIdx = counter;

			counter++;
		}

		ImGui::ListBoxFooter();
		if (ImGui::Button("Remove"))
			removedMeshes.erase(removedMeshes.begin() + selectedIdx);
		ImGui::End();*/

		static bool CB = false;
		static std::string previewValue = "Select a string";
		if (ImGui::BeginCombo("String Colors", previewValue.c_str())) {
			for (int n = 0; n < 6; n++)
			{
				const bool is_selected = (selectedString == n);
				if (ImGui::Selectable(comboStringsItems[n], is_selected, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups))
					selectedString = n;

				if (is_selected) {
					//std::cout << selectedString << std::endl;
					previewValue = std::to_string(selectedString);

					RSColor currColors = Settings.GetCustomColors(CB)[selectedString];
					strR = currColors.r * 255;
					strG = currColors.g * 255;
					strB = currColors.b * 255;
				}
			}
			ImGui::EndCombo();
		}

		ImGui::SliderInt("R", &strR, 0, 255);
		ImGui::SliderInt("G", &strG, 0, 255);
		ImGui::SliderInt("B", &strB, 0, 255);
		ImGui::Checkbox("CB", &CB);

		if (ImGui::Button("Generate Texture")) {
			Settings.SetStringColors(selectedString, Color(strR, strG, strB), CB);
			generateTexture = true;
		}

		if (ImGui::Button("Restore default colors"))
			ERMode.ResetString(selectedString);

		ImGui::End();

		static int selectedValues[12]; // NOTE: this is called every frame, so if you declare your non-static variables here, they will be reset to default values every call - either make them static or declare them globally in the header

		ImGui::Begin("Guitar Speak Settings");
		int optionsImGUI = -1;
		for (int note = 0; note < 12; note++) {
			std::string noteName = GuitarSpeak.noteNames[note];

			if (optionsImGUI > -1 && ImGui::Button("Save Settings")) {
				GuitarSpeak.ForceNewSettings(noteName, GuitarSpeak.keyPressArray[optionsImGUI]);
			}

			if (ImGui::BeginCombo(noteName.c_str(), GuitarSpeakStartingTexts[note].c_str())) {

				for (int options = 0; options < 12; options++)
				{
					bool is_selected = (selectedValues[options] == options);
					if (ImGui::Selectable(GuitarSpeak.keyPressArray[options].c_str(), is_selected, ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups)) {
						selectedValues[options] = options;
						optionsImGUI = options;
					}

					if (is_selected) {
						GuitarSpeakStartingTexts[note] = GuitarSpeak.keyPressArray[options];
					}
				}

				ImGui::EndCombo();
			}
		}

		ImGui::End();

		/*ImGui::Begin("Game colors testing");
		ImGui::SliderInt("Index", &ERMode.currentOffsetIdx, 0, 16);

		char label[10];
		sprintf(label, "0x%03x", (ERMode.currentOffsetIdx * 0x18 + 0x350));

		ImGui::LabelText("Offset:", label);

		ImGui::SliderInt("Black (0) / white (1) ", &ERMode.currColor, 0, 1);

		if (ImGui::Button("Save Defaults")) {
			ERMode.saveDefaults = true;
		}

		if (ImGui::Button("Restore Defaults")) {
			ERMode.restoreDefaults = true;
		}

		ImGui::End();*/
	}

	ImGui::EndFrame();
	ImGui::Render();

	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	if (generateTexture) {
		GenerateTexture(pDevice);
		generateTexture = false;
	}

	return hRet;
}

HRESULT APIENTRY Hook_Reset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters) { //gotta do this so that ALT TAB-ing out of the game doesn't mess the whole thing up
	ImGui_ImplDX9_InvalidateDeviceObjects();

	HRESULT ResetReturn = oReset(pDevice, pPresentationParameters);

	ImGui_ImplDX9_CreateDeviceObjects();

	return ResetReturn;
}

HRESULT APIENTRY Hook_DP(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType, UINT startIndex, UINT primCount) {
	if (pDevice->GetStreamSource(0, &Stream_Data, &Offset, &Stride) == D3D_OK)
		Stream_Data->Release();

	if (Settings.ReturnSettingValue("ExtendedRangeEnabled") == "on" && Stride == 12) { //Stride 12 = tails PogU
		MemHelpers.ToggleCB(MemHelpers.IsExtendedRangeSong());
		pDevice->SetTexture(1, ourTexture);
	}

	return oDrawPrimitive(pDevice, PrimType, startIndex, primCount);
}

HRESULT APIENTRY Hook_DIP(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount) {
	static bool calculatedCRC = false, calculatedHeadstocks = false, calculatedSkyline = false;

	if (pDevice->GetStreamSource(0, &Stream_Data, &Offset, &Stride) == D3D_OK)
		Stream_Data->Release();


	if (Settings.ReturnSettingValue("DiscoModeEnabled") == "on") {
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); // Make AMPS Semi-Transparent <- Is the one that breaks things
		pDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE); // Sticky Colors

		return oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
	}

	if (setAllToNoteGradientTexture) {
		pDevice->SetTexture(currStride, gradientTextureSeven);
		return oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
	}

	Mesh current(Stride, primCount, NumVertices);
	ThiccMesh currentThicc(Stride, primCount, NumVertices, startIndex, mStartregister, PrimType, decl->Type, mVectorCount, numElements);

	if (debug) {
		if (GetAsyncKeyState(VK_PRIOR) & 1 && currIdx < std::size(allMeshes) - 1)//page up
			currIdx++;
		if (GetAsyncKeyState(VK_NEXT) & 1 && currIdx > 0) //page down
			currIdx--;

		if (GetAsyncKeyState(VK_END) & 1) // Toggle logging
			startLogging = !startLogging;

		if (GetAsyncKeyState(VK_F8) & 1) { //save logged meshes to file
			for (auto mesh : allMeshes) {
				Log(mesh.ToString().c_str());
			}
		}

		if (GetAsyncKeyState(VK_F7) & 1) { //save only removed 
			for (auto mesh : removedMeshes) {
				Log(mesh.ToString().c_str());
			}
		}

		if (GetAsyncKeyState(VK_CONTROL) & 1)
			Log("{ %d, %d, %d, %d, %d, %d, %d, %d, %d }, ", Stride, primCount, NumVertices, startIndex, mStartregister, PrimType, decl->Type, mVectorCount, numElements);

		if (startLogging) {
			if (std::find(allMeshes.begin(), allMeshes.end(), currentThicc) == allMeshes.end()) // Make sure we don't log what we'd already logged
				allMeshes.push_back(currentThicc);
			//Log("{ %d, %d, %d},", Stride, primCount, NumVertices); // Log Current Texture -> Mesh
			//Log("{ %d, %d, %d, %d, %d, %d, %d, %d, %d }, ", Stride, primCount, NumVertices, startIndex, mStartregister, PrimType, decl->Type, mVectorCount, numElements); // Log Current Texture -> ThiccMesh
			//Log("%s", MemHelpers.GetCurrentMenu().c_str()); // Log Current Menu
		}

		if (std::size(allMeshes) > 0 && allMeshes.at(currIdx) == currentThicc) {
			currStride = Stride;
			currNumVertices = NumVertices;
			currPrimCount = primCount;
			currStartIndex = startIndex;
			currStartRegister = mStartregister;
			currPrimType = PrimType;
			currDeclType = decl->Type;
			currVectorCount = mVectorCount;
			currNumElements = numElements;
			//pDevice->SetTexture(1, Yellow);
			return D3D_OK;
		}

		if (IsExtraRemoved(removedMeshes, currentThicc))
			return D3D_OK;
	}

	// Mods

	if (Settings.ReturnSettingValue("ExtendedRangeEnabled") == "on" && MemHelpers.IsExtendedRangeSong()) {
		if (IsToBeRemoved(sevenstring, current)) { // Change all pieces of note head's textures
			MemHelpers.ToggleCB(MemHelpers.IsExtendedRangeSong());
			pDevice->SetTexture(1, ourTexture);
		}
		else if (FRETNUM_AND_MISS_INDICATOR && numElements == 7 && mVectorCount == 4 && decl->Type == 2) { // Colors for note stems (part below the note), and note accents
			pDevice->GetTexture(1, &pBaseTexture);
			pCurrTexture = (LPDIRECT3DTEXTURE9)pBaseTexture;

			if (!pBaseTexture)
				return oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);

			if (calculatedCRC) {
				if (std::find(std::begin(notewayTexturePointers), std::end(notewayTexturePointers), pCurrTexture) != std::end(notewayTexturePointers))
					pDevice->SetTexture(1, ourTexture);
			}
			else if (CRCForTexture(pCurrTexture, crc)) { // 0x00090000 - fretnums on noteway, 0x005a00b9 - noteway lanes, 0x00035193 -noteway bgd, 0x00004a4a-noteway lanes left and right of chord shape
				if (crc == 0x02a50002) // Same checksum for stems and accents, because they use the same texture
					AddToTextureList(notewayTexturePointers, pCurrTexture);

				if (notewayTexturePointers.size() == 2) {
					std::cout << "Calculated stem CRC" << std::endl;
					calculatedCRC = true;
				}
			}
			return oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
		}
	}

	else if (GreenScreenWall && IsExtraRemoved(greenScreenWallMesh, currentThicc))
		return D3D_OK;

	if (std::find(std::begin(songModes), std::end(songModes), currentMenu.c_str()) != std::end(songModes)) {
		if (Settings.ReturnSettingValue("FretlessModeEnabled") == "on" && IsExtraRemoved(fretless, currentThicc))
			return D3D_OK;
		if (Settings.ReturnSettingValue("RemoveInlaysEnabled") == "on" && IsExtraRemoved(inlays, currentThicc))
			return D3D_OK;
		if (Settings.ReturnSettingValue("RemoveLaneMarkersEnabled") == "on" && IsExtraRemoved(laneMarkers, currentThicc))
			return D3D_OK;
		if (Settings.ReturnSettingValue("RemoveLyrics") == "on" && IsExtraRemoved(lyrics, currentThicc))
			return D3D_OK;
	}
	else if (std::find(std::begin(tuningMenus), std::end(tuningMenus), MemHelpers.GetCurrentMenu().c_str()) != std::end(tuningMenus))
	{
		if (IsExtraRemoved(tuningLetters, currentThicc)) // This is called to remove those pesky tuning letters that share the same texture values as fret numbers and chord fingerings
			return D3D_OK;
		if (IsExtraRemoved(tunerHighlight, currentThicc)) // This is called to remove the tuner's highlights
			return D3D_OK;
		if (IsExtraRemoved(leftyFix, currentThicc)) // Lefties need their own little place in life...
			return D3D_OK;
	}



	if (!lowPerformancePC) {
		if (toggleSkyline && Stride == 16) {
			if (DrawSkylineInMenu) { // If the user is in "Song" mode for Toggle Skyline and is NOT in a song -> draw the UI
				SkylineOff = false;
				return oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
			}

			// Skyline Removal
			pDevice->GetTexture(1, &pBaseTextures[1]);
			pCurrTextures[1] = (LPDIRECT3DTEXTURE9)pBaseTextures[1];

			if (pBaseTextures[1]) {  // There's only two textures in Stage 1 for meshes with Stride = 16, so we could as well skip CRC calcuation and just check if !pBaseTextures[1] and return D3D_OK directly
				if (CRCForTexture(pCurrTextures[1], crc)) {
					if (crc == 0x65b846aa || crc == 0xbad9e064) { // Purple rectangles + orange line beneath them
						SkylineOff = true;
						return D3D_OK;
					}
				}
			}

			pDevice->GetTexture(0, &pBaseTextures[0]);
			pCurrTextures[0] = (LPDIRECT3DTEXTURE9)pBaseTextures[0];

			if (pBaseTextures[0]) {
				if (CRCForTexture(pCurrTextures[0], crc)) {
					if (crc == 0xc605fbd2 || crc == 0xff1c61ff) {  // There's a few more of textures used in Stage 0, so doing the same is no-go; Shadow-ish thing in the background + backgrounds of rectangles
						SkylineOff = true;
						return D3D_OK;
					}
				}
			}
		}
		else if (Settings.ReturnSettingValue("RemoveHeadstockEnabled") == "on") {
			if (Stride == 44 || Stride == 56 || Stride == 60 || Stride == 68 || Stride == 76 || Stride == 84) { // If we call GetTexture without any filtering, it causes a lockup when ALT-TAB-ing/changing fullscreen to windowed and vice versa
				pDevice->GetTexture(1, &pBaseTextures[1]);
				pCurrTextures[1] = (LPDIRECT3DTEXTURE9)pBaseTextures[1];

				if (resetHeadstockCache && IsExtraRemoved(headstockThicc, currentThicc)) {
					if (!pBaseTextures[1]) //if there's no texture for Stage 1
						return D3D_OK;

					if (CRCForTexture(pCurrTextures[1], crc)) {
						if (crc == 0x008d5439 || crc == 0x000d4439 || crc == 0x00000000 || crc == 0xa55470f6 || crc == 0x008f4039)
							AddToTextureList(headstockTexturePointers, pCurrTextures[1]);
					}

					//Log("0x%08x", crc);

					if (headstockTexturePointers.size() == 3) {
						calculatedHeadstocks = true;
						resetHeadstockCache = false;
						std::cout << "Calculated headstock CRCs (Menu: " << currentMenu << " )" << std::endl;
					}

					return D3D_OK;
				}

				if (calculatedHeadstocks)
					if (std::find(std::begin(headstockTexturePointers), std::end(headstockTexturePointers), pCurrTextures[1]) != std::end(headstockTexturePointers))
						return D3D_OK;
			}
		}
	}
	return oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

HRESULT APIENTRY Hook_SetVertexDeclaration(LPDIRECT3DDEVICE9 pDevice, IDirect3DVertexDeclaration9* pdecl) {
	if (pdecl != NULL)
		pdecl->GetDeclaration(decl, &numElements);

	return oSetVertexDeclaration(pDevice, pdecl);
}

HRESULT APIENTRY Hook_SetVertexShaderConstantF(LPDIRECT3DDEVICE9 pDevice, UINT StartRegister, const float* pConstantData, UINT Vector4fCount) {
	if (pConstantData != NULL) {
		mStartregister = StartRegister;
		mVectorCount = Vector4fCount;
	}

	return oSetVertexShaderConstantF(pDevice, StartRegister, pConstantData, Vector4fCount);
}

HRESULT APIENTRY Hook_SetVertexShader(LPDIRECT3DDEVICE9 pDevice, IDirect3DVertexShader9* veShader) {
	if (veShader != NULL) {
		vShader = veShader;
		vShader->GetFunction(NULL, &vSize);
	}

	return oSetVertexShader(pDevice, veShader);
}

HRESULT APIENTRY Hook_SetPixelShader(LPDIRECT3DDEVICE9 pDevice, IDirect3DPixelShader9* piShader) {
	if (piShader != NULL) {
		pShader = piShader;
		pShader->GetFunction(NULL, &pSize);
	}

	return oSetPixelShader(pDevice, piShader);
}

HRESULT APIENTRY Hook_SetStreamSource(LPDIRECT3DDEVICE9 pDevice, UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride) {
	D3DVERTEXBUFFER_DESC desc;

	if (Stride == 32 && numElements == 8 && mVectorCount == 4 && decl->Type == 2) { // Remove Line Markers
		pStreamData->GetDesc(&desc);
		vertexBufferSize = desc.Size;
	}

	return oSetStreamSource(pDevice, StreamNumber, pStreamData, OffsetInBytes, Stride);
}

void GUI() {
	DWORD d3d9Base, adr, * vTable = NULL;
	while ((d3d9Base = (DWORD)GetModuleHandleA("d3d9.dll")) == NULL) //aight ffio ;)
		Sleep(500);

	adr = MemUtil.FindPattern(d3d9Base, Offsets.d3dDevice_SearchLen, (PBYTE)Offsets.d3dDevice_Pattern, Offsets.d3dDevice_Mask) + 2; //and that's it... (:

	if (!adr) {
		std::cout << "Could not find D3D9 device pointer" << std::endl;
		return;
	}

	vTable = *(DWORD**)adr;
	if (!vTable) {
		std::cout << "Could not find game device's vTable address" << std::endl;
		return;
	}

	oSetVertexDeclaration = (tSetVertexDeclaration)MemUtil.TrampHook((PBYTE)vTable[D3DInfo::SetVertexDeclaration_Index], (PBYTE)Hook_SetVertexDeclaration, 7);
	oSetVertexShader = (tSetVertexShader)MemUtil.TrampHook((PBYTE)vTable[D3DInfo::SetVertexShader_Index], (PBYTE)Hook_SetVertexShader, 7);
	oSetVertexShaderConstantF = (tSetVertexShaderConstantF)MemUtil.TrampHook((PBYTE)vTable[D3DInfo::SetVertexShaderConstantF_Index], (PBYTE)Hook_SetVertexShaderConstantF, 7);
	oSetPixelShader = (tSetPixelShader)MemUtil.TrampHook((PBYTE)vTable[D3DInfo::SetPixelShader_Index], (PBYTE)Hook_SetPixelShader, 7);
	oSetStreamSource = (tSetStreamSource)MemUtil.TrampHook((PBYTE)vTable[D3DInfo::SetStreamSource_Index], (PBYTE)Hook_SetStreamSource, 7);

	oReset = (tReset)DetourFunction((PBYTE)vTable[D3DInfo::Reset_Index], (PBYTE)Hook_Reset);
	oEndScene = (tEndScene)MemUtil.TrampHook((PBYTE)vTable[D3DInfo::EndScene_Index], (PBYTE)Hook_EndScene, 7);
	oDrawIndexedPrimitive = (tDrawIndexedPrimitive)MemUtil.TrampHook((PBYTE)vTable[D3DInfo::DrawIndexedPrimitive_Index], (PBYTE)Hook_DIP, 5);
	oDrawPrimitive = (tDrawPrimitive)MemUtil.TrampHook((PBYTE)vTable[D3DInfo::DrawPrimitive_Index], (PBYTE)Hook_DP, 7);
}

void InitEngineFunctions() {
	SetRTPCValue = (tSetRTPCValue)Offsets.func_SetRTPCValue;
	GetRTPCValue = (tGetRTPCValue)Offsets.func_GetRTPCValue;
}

void AutoEnterGame() {	//very big brain || "Fork in the toaster"
	PostMessage(FindWindow(NULL, L"Rocksmith 2014"), WM_KEYDOWN, VK_RETURN, 0);
	Sleep(30);
	PostMessage(FindWindow(NULL, L"Rocksmith 2014"), WM_KEYUP, VK_RETURN, 0);
}

void UpdateSettings() { // Live updates from the INI
	Settings.UpdateSettings();
	Sleep(500);
	CustomSongTitles.LoadSettings();
	Sleep(500);
	CustomSongTitles.HookSongListsKoko();
	Sleep(500);
}

void ClearLogs() { // Not taken from here: https://stackoverflow.com/questions/6935279/delete-all-txt-in-a-directory-with-c :P
	if (debug) {
		std::string command = "del /Q ";
		std::string path = "*.mdmp";
		system(command.append(path).c_str());

		std::cout << "Deleting Useless Log Files" << std::endl;
	}
}

unsigned WINAPI MainThread(void*) {
	Offsets.Initialize();
	MemHelpers.PatchCDLCCheck();

	UpdateSettings();

	ERMode.Initialize();

	GUI();
	InitEngineFunctions();

	ClearLogs(); // Delete's those stupid log files Rocksmith loves making.

	while (true) {
		Sleep(2000);

		currentMenu = MemHelpers.GetCurrentMenu();

		if (GameLoaded) // If Game Is Loaded (No need to run these while the game is loading.)
		{

			ERMode.Toggle7StringMode();

			if (std::find(std::begin(lessonModes), std::end(lessonModes), currentMenu.c_str()) != std::end(lessonModes)) // Is User In A Lesson
				LessonMode = true;
			else
				LessonMode = false;

			if (LessonMode && Settings.ReturnSettingValue("ToggleLoftEnabled") == "on" && Settings.ReturnSettingValue("ToggleLoftWhen") != "manual") { // Is User In A Lesson Mode AND set to turn loft off
				if (LoftOff)
					MemHelpers.ToggleLoft();
				LoftOff = false;
				GreenScreenWall = true;
			}

			if (!LoftOff && !LessonMode && Settings.ReturnSettingValue("ToggleLoftEnabled") == "on" && Settings.ReturnSettingValue("ToggleLoftWhen") == "startup") { // Turn the loft off on startup
				MemHelpers.ToggleLoft();
				LoftOff = true;
				GreenScreenWall = false;
			}
			if (!SkylineOff && Settings.ReturnSettingValue("RemoveSkylineEnabled") == "on" && Settings.ReturnSettingValue("ToggleSkylineWhen") == "startup") { // Turn the skyline off on startup
				toggleSkyline = true;
			}

			if (std::find(std::begin(songModes), std::end(songModes), currentMenu.c_str()) != std::end(songModes)) // If User Is Entering Song
			{
				GuitarSpeakPresent = false;

				if (Settings.ReturnSettingValue("ToggleLoftEnabled") == "on" && Settings.ReturnSettingValue("ToggleLoftWhen") == "song") // Turn the loft off when entering a song
				{
					if (!LoftOff)
						MemHelpers.ToggleLoft();
					LoftOff = true;
				}

				if (Settings.ReturnSettingValue("RemoveSkylineEnabled") == "on" && Settings.ReturnSettingValue("ToggleSkylineWhen") == "song") // Turn the skyline off when entering a song
				{
					if (!SkylineOff)
						toggleSkyline = true;
					DrawSkylineInMenu = false;
				}
			}
			else // If User Is Exiting Song / In A Menu
			{
				if (Settings.ReturnSettingValue("ToggleLoftEnabled") == "on" && Settings.ReturnSettingValue("ToggleLoftWhen") == "song") { // Turn the loft back on after exiting a song
					if (LoftOff) {
						MemHelpers.ToggleLoft();
						LoftOff = false;
					}
					if (!LessonMode)
					{
						GreenScreenWall = false;
					}
				}
				if (SkylineOff && Settings.ReturnSettingValue("RemoveSkylineEnabled") == "on" && Settings.ReturnSettingValue("ToggleSkylineWhen") == "song") { // Turn the skyline back on after exiting a song
					toggleSkyline = true;
					DrawSkylineInMenu = true;
				}

				/*if(!GuitarSpeakPresent) {
					GuitarSpeakPresent = true;
					GuitarSpeak.TimerTick();
				}*/

				//UpdateSettings(); // A little flaky right now, it likes to crash after a couple setting changes. | Disco mode skyline modification doesn't change back?


				if (Settings.ReturnSettingValue("RemoveHeadstockEnabled") == "on" && (!(std::find(std::begin(tuningMenus), std::end(tuningMenus), currentMenu.c_str()) != std::end(tuningMenus)) || currentMenu.c_str() == "MissionMenu")) // Can we reset the headstock cache without the user noticing?
					resetHeadstockCache = true;

			}

			if (previousMenu != currentMenu && std::find(std::begin(tuningMenus), std::end(tuningMenus), currentMenu) != std::end(tuningMenus)) { // If the current menu is not the same as the previous menu and if it's one of menus where you tune your guitar (i.e. headstock is shown), reset the cache because user may want to change the headstock style
				resetHeadstockCache = true;
				headstockTexturePointers.clear();
			}
			previousMenu = currentMenu;
		}
		else // Game Hasn't Loaded Yet
		{
			if (MemHelpers.GetCurrentMenu() == "MainMenu") // Yay We Loaded :P
				GameLoaded = true;

			if (Settings.ReturnSettingValue("ForceProfileEnabled") == "on" && !(std::find(std::begin(dontAutoEnter), std::end(dontAutoEnter), currentMenu) != std::end(dontAutoEnter))) // "Fork in the toaster" / Spam Enter Method
				AutoEnterGame();
		}

		if (enableColorBlindCheckboxGUI)
			MemHelpers.ToggleCB(cbEnabled);

		ERMode.DoRainbow();
	}

	return 0;
}


void Initialize(void) {
	_beginthreadex(NULL, 0, &MainThread, NULL, 0, 0);
	_beginthreadex(NULL, 0, &EnumerationThread, NULL, 0, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		AllocConsole();
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		DisableThreadLibraryCalls(hModule);

		InitProxy();
		Initialize();
		return TRUE;
	case DLL_PROCESS_DETACH:
		ShutdownProxy();
		ImGui_ImplWin32_Shutdown();
		ImGui_ImplDX9_Shutdown();
		ImGui::DestroyContext();
		return TRUE;
	}
	return TRUE;
}
