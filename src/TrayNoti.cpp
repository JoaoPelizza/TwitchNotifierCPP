#include "../include/TrayNoti.hpp"
#include "../include/FileManager.hpp"
#include "../include/ConnectionManager.hpp"

TrayNoti::TrayNoti(int screenX, int screenY){
    this->screenX = screenX;
    this->screenY = screenY;
    if(!QSystemTrayIcon::isSystemTrayAvailable()){
        return;
    }
    trayIcon        = new QSystemTrayIcon();
    trayContextMenu = new QMenu();
    timer           = new QTimer();
    icon            = new QIcon();

    setTrayIcon(iconPath);
    trayIcon->setContextMenu(trayContextMenu);
}

TrayNoti::TrayNoti(std::string iconPath){
    
    if(!QSystemTrayIcon::isSystemTrayAvailable()){
        return;
    }
    trayIcon        = new QSystemTrayIcon();
    trayContextMenu = new QMenu();
    timer           = new QTimer();
    icon            = new QIcon();

    setTrayIcon(iconPath);
    this->iconPath = iconPath;
    trayIcon->setContextMenu(trayContextMenu);
}


void TrayNoti::addToActionList(std::vector<struct liveChannelInfo> lciVec){
    QAction *action = new QAction();
    QSignalMapper* signalMapper = new QSignalMapper();
    bool aux = false;
    bool noti = false;
    for(auto vecPointer = lciVec.begin(); vecPointer!=lciVec.end(); vecPointer++){

        for(auto it = trayContextMenu->actions().begin(); it!= trayContextMenu->actions().end(); it++){
            if(!(*vecPointer).userName.compare((*it)->text().toStdString())){
                aux = true;
            }
        }
        if(!aux){
            noti = true;
            action->setIcon(QIcon((iconPath+(*vecPointer).userId+".png").c_str()));
            action->setText((*vecPointer).userName.c_str());
            this->auxString = (*(vecPointer)).userName;
            QObject::connect(action,&QAction::triggered,this,[this](){TrayNoti::trayOpenLink(auxString);});
            actionVec.push_back(action);
            action = new QAction();
        }
        aux = false;
    }
    if(noti) notiIcon();
}

void TrayNoti::addToMenu(){

    for(auto vecPointer = actionVec.begin(); vecPointer != actionVec.end();vecPointer++){
        trayContextMenu->addAction(*(vecPointer));
    }
    this->actionVec.clear();

}

void TrayNoti::cleanMenu(std::vector<struct liveChannelInfo> lciVec){
    int counter = 0;
    bool aux = false;

    for(auto trayPointer : trayContextMenu->actions()){
        std::string auxString = (trayPointer)->text().toStdString();

        for(auto it = lciVec.begin(); it!= lciVec.end(); it++){
            if(!(*it).userName.compare((auxString))){
                aux = true;
                break;
            }
        }

        if(!aux){
            trayContextMenu->removeAction(*(trayContextMenu->actions().begin()+counter));
            counter--;
        }
        counter++;

        aux = false;
    }
}

int TrayNoti::getTrayContextMenuActionsListSize(){
    return trayContextMenu->actions().size();
}

void TrayNoti::trayOpenLink(std::string chanName){
    system(("firefox https://twitch.tv/"+chanName).c_str());
}

void TrayNoti::notiIcon(){
    QIcon *swapIcon = new QIcon;
    for(int i =0 ; i<2;i++){
        swapIcon->addFile(("./twiNotiIcons/" + color[notiPoint] + "/" + states[state]+ ".png").c_str(),QSize(22,22));
        trayIcon->setIcon(*swapIcon);
        sleep(1);
        swapIcon->addFile(("./twiNotiIcons/" + color[notiColor] + "/" + states[state]+ ".png").c_str(),QSize(22,22));
        trayIcon->setIcon(*swapIcon);
        sleep(1);
    }
}

void TrayNoti::changeIcon(int newIconState){
    setIconState(newIconState);
    notiIcon();
}

void TrayNoti::setIconState(int newIconState){
    this->state = newIconState;
}

void TrayNoti::setTrayIcon(std::string path){
    this->icon->addFile(("./twiNotiIcons/" + color[notiColor] +"/common.png").c_str(),QSize(22,22));
    trayIcon->setIcon(*icon);
    trayIcon->show();
}

//DEPRICATED

void TrayNoti::checkNotifications(){
    
    QMessageBox* msgbox = new QMessageBox(QMessageBox::NoIcon,NULL,"",
    QMessageBox::StandardButton::NoButton,
    NULL,Qt::Popup | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint | Qt::WindowDoesNotAcceptFocus);
    msgbox->setStyleSheet("QMessageBox{messagebox-text-interaction-flags: 5}");
    msgbox->setTextInteractionFlags(Qt::NoTextInteraction);
    /*remove "okay" button*/
    //msgbox->setStandardButtons(0);
    //size.scale(screenX,screenY,Qt::KeepAspectRatio);
    QObject::connect(timer, SIGNAL(timeout()), msgbox, SLOT(close()));
    QObject::connect(timer, SIGNAL(timeout()), timer, SLOT(stop()));
    QObject::connect(timer, SIGNAL(timeout()), timer, SLOT(deleteLater()));
    timer->start(2500);

    msgbox->setText("<div align='justified'><div style='display: flex'><img src='39322714.png' width='80' height='80'></div><div align='right'>Suicidio online</div></div>");



    msgbox->move(QPoint(this->screenX -(250),25));
    msgbox->setWindowOpacity(0.90);
    msgbox->setMinimumSize(QSize(600, 600));
    msgbox->raise();
    msgbox->open();
}