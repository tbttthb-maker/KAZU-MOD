#import "PubgLoad.h"
#import "metalbiew.h"
#import "FutureESP.h"

/********************************************
 * Developer: KAZU
 * Project: KAZU-MOD
 * Telegram: https://t.me/K_4441
 ********************************************/

extern bool MenDeal;
FutureESP* g_ESP = new FutureESP(); 

@interface ImGuiLoad()
@property (nonatomic, strong) metalbiew *vna;
@end

@implementation ImGuiLoad

+ (void)load
{
    // Delay initialization to ensure the game environment is ready
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [[self share] initTapGes];
        
        // Pre-initialize the ESP view layer automatically on startup
        [[self share] setupESPView];
    });
}

+ (instancetype)share
{
    static ImGuiLoad *tool;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        tool = [[ImGuiLoad alloc] init];
    });
    return tool;
}

// Setup the drawing layer (Metal) to be ready for ESP rendering
- (void)setupESPView 
{
    if (!_vna) {
        _vna = [[metalbiew alloc] init];
        // Add the drawing view to the main window
        [[UIApplication sharedApplication].windows[0].rootViewController.view addSubview:_vna.view];
        MenDeal = false; 
    }
}

-(void)initTapGes
{
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] init];
    tap.numberOfTapsRequired = 3;   // 3 Taps
    tap.numberOfTouchesRequired = 3; // 3 Fingers
    [[UIApplication sharedApplication].windows[0].rootViewController.view addGestureRecognizer:tap];
    [tap addTarget:self action:@selector(show)];
}

- (void)show
{
    // Toggle the Menu UI visibility
    if (!_vna) {
        [self setupESPView];
    }
    
    MenDeal = !MenDeal; 
}

@end
