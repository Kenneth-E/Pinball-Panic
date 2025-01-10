import SwiftUI
import AppKit

// Initialize the application first
let app = NSApplication.shared
app.setActivationPolicy(.regular)

class AppDelegate: NSObject, NSApplicationDelegate {
    var window: NSWindow?
    
    func applicationDidFinishLaunching(_ notification: Notification) {
        print("App launching...")  // Debug print
        
        // Set up menu bar
        let menuBar = NSMenu()
        NSApp.mainMenu = menuBar
        
        let appMenu = NSMenu()
        let appName = ProcessInfo.processInfo.processName
        let quitTitle = "Quit \(appName)"
        appMenu.addItem(NSMenuItem(title: quitTitle, 
                                 action: #selector(NSApplication.terminate(_:)), 
                                 keyEquivalent: "q"))
        
        let appMenuItem = NSMenuItem()
        appMenuItem.submenu = appMenu
        menuBar.addItem(appMenuItem)
        
        print("Creating view...")  // Debug print
        let contentView = GridView()
            .frame(idealWidth: 400, idealHeight: 400)
        
        print("Creating window...")  // Debug print
        window = NSWindow(
            contentRect: NSRect(x: 0, y: 0, width: 400, height: 450),
            styleMask: [.titled, .closable, .miniaturizable, .resizable],
            backing: .buffered,
            defer: false
        )
        
        window?.contentView = NSHostingView(rootView: contentView)
        window?.title = "Pinball Panic"
        window?.center()
        window?.makeKeyAndOrderFront(nil)
        NSApp.activate(ignoringOtherApps: true)
        print("Window should be visible now")  // Debug print
    }
    
    func applicationShouldTerminateAfterLastWindowClosed(_ sender: NSApplication) -> Bool {
        return true
    }
}

// Set up and run the application
let delegate = AppDelegate()
app.delegate = delegate
app.run()
