struct Settings : Markup::Node {
  Settings();
  auto save() -> void;
};

struct VideoSettings : TabFrameItem {
  VideoSettings(TabFrame*);

public:
  VerticalLayout layout{this};
    Label colorAdjustmentLabel{&layout, Size{~0, 0}, 2};
    TableLayout colorLayout{&layout, Size{~0, 0}};
      Label luminanceLabel{&colorLayout, Size{0, 0}};
      Label luminanceValue{&colorLayout, Size{50, 0}};
      HorizontalSlider luminanceSlider{&colorLayout, Size{~0, 0}};
    //
      Label saturationLabel{&colorLayout, Size{0, 0}};
      Label saturationValue{&colorLayout, Size{50, 0}};
      HorizontalSlider saturationSlider{&colorLayout, Size{~0, 0}};
    //
      Label gammaLabel{&colorLayout, Size{0, 0}};
      Label gammaValue{&colorLayout, Size{50, 0}};
      HorizontalSlider gammaSlider{&colorLayout, Size{~0, 0}};
};

struct AudioSettings : TabFrameItem {
  AudioSettings(TabFrame*);

public:
  VerticalLayout layout{this};
    Label effectsLabel{&layout, Size{~0, 0}, 2};
    TableLayout effectsLayout{&layout, Size{~0, 0}};
      Label skewLabel{&effectsLayout, Size{0, 0}};
      Label skewValue{&effectsLayout, Size{50, 0}};
      HorizontalSlider skewSlider{&effectsLayout, Size{~0, 0}};
    //
      Label volumeLabel{&effectsLayout, Size{0, 0}};
      Label volumeValue{&effectsLayout, Size{50, 0}};
      HorizontalSlider volumeSlider{&effectsLayout, Size{~0, 0}};
    //
      Label balanceLabel{&effectsLayout, Size{0, 0}};
      Label balanceValue{&effectsLayout, Size{50, 0}};
      HorizontalSlider balanceSlider{&effectsLayout, Size{~0, 0}};
};

struct InputSettings : TabFrameItem {
  InputSettings(TabFrame*);
  auto updateControls() -> void;
  auto activePort() -> InputPort&;
  auto activeDevice() -> InputDevice&;
  auto reloadPorts() -> void;
  auto reloadDevices() -> void;
  auto reloadMappings() -> void;
  auto refreshMappings() -> void;
  auto assignMapping() -> void;
  auto cancelMapping() -> void;
  auto assignMouseInput(uint id) -> void;
  auto inputEvent(shared_pointer<HID::Device> device, uint group, uint input, int16 oldValue, int16 newValue, bool allowMouseInput = false) -> void;

public:
  maybe<InputMapping&> activeMapping;
  Timer timer;

  VerticalLayout layout{this};
    HorizontalLayout selectionLayout{&layout, Size{~0, 0}};
      Label portLabel{&selectionLayout, Size{0, 0}};
      ComboButton portList{&selectionLayout, Size{~0, 0}};
      Label deviceLabel{&selectionLayout, Size{0, 0}};
      ComboButton deviceList{&selectionLayout, Size{~0, 0}};
      Label turboLabel{&selectionLayout, Size{0, 0}};
      ComboButton turboList{&selectionLayout, Size{0, 0}};
    TableView mappingList{&layout, Size{~0, ~0}};
    HorizontalLayout controlLayout{&layout, Size{~0, 0}};
      Button assignMouse1{&controlLayout, Size{100, 0}};
      Button assignMouse2{&controlLayout, Size{100, 0}};
      Button assignMouse3{&controlLayout, Size{100, 0}};
      Widget controlSpacer{&controlLayout, Size{~0, 0}};
      Button assignButton{&controlLayout, Size{80, 0}};
      Button clearButton{&controlLayout, Size{80, 0}};
};

struct HotkeySettings : TabFrameItem {
  HotkeySettings(TabFrame*);
  auto reloadMappings() -> void;
  auto refreshMappings() -> void;
  auto assignMapping() -> void;
  auto cancelMapping() -> void;
  auto inputEvent(shared_pointer<HID::Device> device, uint group, uint input, int16 oldValue, int16 newValue) -> void;

public:
  maybe<InputMapping&> activeMapping;
  Timer timer;

  VerticalLayout layout{this};
    TableView mappingList{&layout, Size{~0, ~0}};
    HorizontalLayout controlLayout{&layout, Size{~0, 0}};
      Widget controlSpacer{&controlLayout, Size{~0, 0}};
      Button assignButton{&controlLayout, Size{80, 0}};
      Button clearButton{&controlLayout, Size{80, 0}};
};

struct PathSettings : TabFrameItem {
  PathSettings(TabFrame*);
  auto refreshPaths() -> void;

public:
  TableLayout layout{this};
    Label gamesLabel{&layout, Size{0, 0}};
    LineEdit gamesPath{&layout, Size{~0, 0}};
    Button gamesAssign{&layout, Size{80, 0}};
    Button gamesReset{&layout, Size{80, 0}};
  //
    Label patchesLabel{&layout, Size{0, 0}};
    LineEdit patchesPath{&layout, Size{~0, 0}};
    Button patchesAssign{&layout, Size{80, 0}};
    Button patchesReset{&layout, Size{80, 0}};
  //
    Label savesLabel{&layout, Size{0, 0}};
    LineEdit savesPath{&layout, Size{~0, 0}};
    Button savesAssign{&layout, Size{80, 0}};
    Button savesReset{&layout, Size{80, 0}};
  //
    Label cheatsLabel{&layout, Size{0, 0}};
    LineEdit cheatsPath{&layout, Size{~0, 0}};
    Button cheatsAssign{&layout, Size{80, 0}};
    Button cheatsReset{&layout, Size{80, 0}};
  //
    Label statesLabel{&layout, Size{0, 0}};
    LineEdit statesPath{&layout, Size{~0, 0}};
    Button statesAssign{&layout, Size{80, 0}};
    Button statesReset{&layout, Size{80, 0}};
  //
    Label screenshotsLabel{&layout, Size{0, 0}};
    LineEdit screenshotsPath{&layout, Size{~0, 0}};
    Button screenshotsAssign{&layout, Size{80, 0}};
    Button screenshotsReset{&layout, Size{80, 0}};
};

struct ConfigurationSettings : TabFrameItem {
  ConfigurationSettings(TabFrame*);
  auto updateConfiguration() -> void;

public:
  VerticalLayout layout{this};
    Label optionsLabel{&layout, Size{~0, 0}, 2};
    HorizontalLayout inputFocusLayout{&layout, Size{~0, 0}};
      Label inputFocusLabel{&inputFocusLayout, Size{0, 0}};
      RadioLabel pauseEmulation{&inputFocusLayout, Size{0, 0}};
      RadioLabel blockInput{&inputFocusLayout, Size{0, 0}};
      RadioLabel allowInput{&inputFocusLayout, Size{0, 0}};
      Group inputFocusGroup{&pauseEmulation, &blockInput, &allowInput};
    CheckLabel warnOnUnverifiedGames{&layout, Size{~0, 0}};
    CheckLabel autoSaveMemory{&layout, Size{~0, 0}};
    HorizontalLayout autoStateLayout{&layout, Size{~0, 0}};
      CheckLabel autoSaveStateOnUnload{&autoStateLayout, Size{0, 0}};
      CheckLabel autoLoadStateOnLoad{&autoStateLayout, Size{0, 0}};
    CheckLabel suppressScreenSaver{&layout, Size{~0, 0}};
    Label hacksLabel{&layout, Size{~0, 0}, 2};
    HorizontalLayout fastPPULayout{&layout, Size{~0, 0}};
      CheckLabel fastPPUOption{&fastPPULayout, Size{0, 0}};
      CheckLabel noSpriteLimit{&fastPPULayout, Size{0, 0}};
      CheckLabel hiresMode7{&fastPPULayout, Size{0, 0}};
    CheckLabel fastDSPOption{&layout, Size{~0, 0}};
    HorizontalLayout superFXLayout{&layout, Size{~0, 0}};
      Label superFXLabel{&superFXLayout, Size{0, 0}};
      Label superFXValue{&superFXLayout, Size{50, 0}};
      HorizontalSlider superFXClock{&superFXLayout, Size{~0, 0}};
    Label hacksNote{&layout, Size{~0, 0}};
};

struct DriverSettings : TabFrameItem {
  DriverSettings(TabFrame*);
  auto videoDriverChanged() -> void;
  auto videoDriverChange() -> void;
  auto videoFormatChanged() -> void;
  auto videoFormatChange() -> void;
  auto audioDriverChanged() -> void;
  auto audioDriverChange() -> void;
  auto audioDeviceChanged() -> void;
  auto audioDeviceChange() -> void;
  auto audioFrequencyChanged() -> void;
  auto audioFrequencyChange() -> void;
  auto audioLatencyChanged() -> void;
  auto audioLatencyChange() -> void;
  auto inputDriverChanged() -> void;
  auto inputDriverChange() -> void;

public:
  VerticalLayout layout{this};
    Label videoLabel{&layout, Size{~0, 0}, 2};
    TableLayout videoLayout{&layout, Size{~0, 0}};
      Label videoDriverLabel{&videoLayout, Size{0, 0}};
      HorizontalLayout videoDriverLayout{&videoLayout, Size{~0, 0}};
        ComboButton videoDriverOption{&videoDriverLayout, Size{0, 0}};
        Button videoDriverUpdate{&videoDriverLayout, Size{0, 0}};
        Label videoDriverActive{&videoDriverLayout, Size{0, 0}};
      Label videoFormatLabel{&videoLayout, Size{0, 0}};
      HorizontalLayout videoPropertyLayout{&videoLayout, Size{~0, 0}};
        ComboButton videoFormatOption{&videoPropertyLayout, Size{0, 0}};
    HorizontalLayout videoToggleLayout{&layout, Size{~0, 0}};
      CheckLabel videoExclusiveToggle{&videoToggleLayout, Size{0, 0}};
      CheckLabel videoBlockingToggle{&videoToggleLayout, Size{0, 0}};
      CheckLabel videoFlushToggle{&videoToggleLayout, Size{0, 0}};
    Label audioLabel{&layout, Size{~0, 0}, 2};
    TableLayout audioLayout{&layout, Size{~0, 0}};
      Label audioDriverLabel{&audioLayout, Size{0, 0}};
      HorizontalLayout audioDriverLayout{&audioLayout, Size{~0, 0}};
        ComboButton audioDriverOption{&audioDriverLayout, Size{0, 0}};
        Button audioDriverUpdate{&audioDriverLayout, Size{0, 0}};
        Label audioDriverActive{&audioDriverLayout, Size{0, 0}};
      Label audioDeviceLabel{&audioLayout, Size{0, 0}};
      HorizontalLayout audioPropertyLayout{&audioLayout, Size{~0, 0}};
        ComboButton audioDeviceOption{&audioPropertyLayout, Size{0, 0}};
        Label audioFrequencyLabel{&audioPropertyLayout, Size{0, 0}};
        ComboButton audioFrequencyOption{&audioPropertyLayout, Size{0, 0}};
        Label audioLatencyLabel{&audioPropertyLayout, Size{0, 0}};
        ComboButton audioLatencyOption{&audioPropertyLayout, Size{0, 0}};
    HorizontalLayout audioToggleLayout{&layout, Size{~0, 0}};
      CheckLabel audioExclusiveToggle{&audioToggleLayout, Size{0, 0}};
      CheckLabel audioBlockingToggle{&audioToggleLayout, Size{0, 0}};
      CheckLabel audioDynamicToggle{&audioToggleLayout, Size{0, 0}};
    Label inputLabel{&layout, Size{~0, 0}, 2};
    TableLayout inputLayout{&layout, Size{~0, 0}};
      Label inputDriverLabel{&inputLayout, Size{0, 0}};
      HorizontalLayout inputDriverLayout{&inputLayout, Size{~0, 0}};
        ComboButton inputDriverOption{&inputDriverLayout, Size{0, 0}};
        Button inputDriverUpdate{&inputDriverLayout, Size{0, 0}};
        Label inputDriverActive{&inputDriverLayout, Size{0, 0}};
};

struct SettingsWindow : Window {
  SettingsWindow();
  auto setVisible(bool visible = true) -> SettingsWindow&;
  auto show(uint index) -> void;

public:
  VerticalLayout layout{this};
    TabFrame panel{&layout, Size{~0, ~0}};
      VideoSettings video{&panel};
      AudioSettings audio{&panel};
      InputSettings input{&panel};
      HotkeySettings hotkeys{&panel};
      PathSettings paths{&panel};
      ConfigurationSettings configuration{&panel};
      DriverSettings drivers{&panel};
  StatusBar statusBar{this};
};

extern Settings settings;
extern unique_pointer<SettingsWindow> settingsWindow;