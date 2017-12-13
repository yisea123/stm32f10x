#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "socket.h"
#include "dhcp.h"
#include "proj_conf.h"
#include "w5500_port.h"

u8 w5500_buffer[DATA_BUF_SIZE];                // maybe dynamic allocate

void w5500_spi_init(void)
{
        SPI_InitTypeDef SPI_InitStructure;
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);

        /* Configure SPIy pins: SCK, MISO and MOSI */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        // CS
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        GPIO_SetBits(GPIOC, GPIO_Pin_9);

        /* SPI Config -------------------------------------------------------------*/
        SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
        SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
        SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
        SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
        SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
        SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
        SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
        SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
        SPI_InitStructure.SPI_CRCPolynomial = 7;

        SPI_Init(SPI2, &SPI_InitStructure);
        SPI_Cmd(SPI2, ENABLE);
}

void w5500_cs_select(void)
{
        GPIO_ResetBits(GPIOC, GPIO_Pin_9);
}

void w5500_cs_deselect(void)
{
        GPIO_SetBits(GPIOC, GPIO_Pin_9);
}

void w5500_spi_send_byte(u8 byte)
{
        while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);

        SPI_I2S_SendData(SPI2, byte);
}

u8 w5500_spi_read_byte(void)
{
        while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

        return SPI_I2S_ReceiveData(SPI2);
}

void ioLibrary_fun_register(void)
{
        reg_wizchip_cris_cbfunc(vPortEnterCritical, vPortExitCritical);
        reg_wizchip_cs_cbfunc(w5500_cs_select, w5500_cs_deselect);
        reg_wizchip_spi_cbfunc(w5500_spi_read_byte, w5500_spi_send_byte);
}

wiz_NetInfo w5500_eth_info = {
        .mac = {0x00, 0x08, 0xdc,0x00, 0xab, 0xcd},
        .ip = {192, 168, 1, 123},
        .sn = {255,255,255,0},
        .gw = {192, 168, 1, 1},
        .dns = {0,0,0,0},
        .dhcp = NETINFO_DHCP
};

void network_init(void)
{
        // Set Network information from netinfo structure
        ctlnetwork(CN_SET_NETINFO, (void*)&w5500_eth_info);

#if DEBUG_OUTPUT_ENABLE == 1
        uint8_t tmpstr[6] = {0,};
        wiz_NetInfo netinfo;
        // Get Network information
        ctlnetwork(CN_GET_NETINFO, (void*)&netinfo);

        // Display Network Information
        ctlwizchip(CW_GET_ID,(void*)tmpstr);

        if(netinfo.dhcp == NETINFO_DHCP)
                LOG_OUT(LOG_INFO "\r\n=== %s NET CONF : DHCP ===\r\n",(char*)tmpstr);
        else
                LOG_OUT(LOG_INFO "\r\n=== %s NET CONF : Static ===\r\n",(char*)tmpstr);

        LOG_OUT(LOG_INFO "MAC: %02X:%02X:%02X:%02X:%02X:%02X\r\n",netinfo.mac[0],netinfo.mac[1],netinfo.mac[2],netinfo.mac[3],netinfo.mac[4],netinfo.mac[5]);
        LOG_OUT(LOG_INFO "SIP: %d.%d.%d.%d\r\n", netinfo.ip[0],netinfo.ip[1],netinfo.ip[2],netinfo.ip[3]);
        LOG_OUT(LOG_INFO "GAR: %d.%d.%d.%d\r\n", netinfo.gw[0],netinfo.gw[1],netinfo.gw[2],netinfo.gw[3]);
        LOG_OUT(LOG_INFO "SUB: %d.%d.%d.%d\r\n", netinfo.sn[0],netinfo.sn[1],netinfo.sn[2],netinfo.sn[3]);
        LOG_OUT(LOG_INFO "DNS: %d.%d.%d.%d\r\n", netinfo.dns[0],netinfo.dns[1],netinfo.dns[2],netinfo.dns[3]);
        LOG_OUT(LOG_INFO "===========================\r\n");
#endif
}

void w5500_ip_assign(void)
{
        getIPfromDHCP(w5500_eth_info.ip);
        getGWfromDHCP(w5500_eth_info.gw);
        getSNfromDHCP(w5500_eth_info.sn);
        getDNSfromDHCP(w5500_eth_info.dns);
        w5500_eth_info.dhcp = NETINFO_DHCP;
        /* Network initialization */
        network_init();      // apply from dhcp
#ifdef _MAIN_DEBUG_
        LOG_OUT(LOG_INFO "DHCP LEASED TIME : %ld Sec.\r\n", getDHCPLeasetime());
#endif
}

void w5500_ip_conflict(void)
{
#ifdef _MAIN_DEBUG_
        LOG_OUT(LOG_ERR "CONFLICT IP from DHCP\r\n");
#endif
        //halt or reset or any...
        while(1); // this example is halt.
}

void w5500_init(void)
{
        s8 rtl = 0;

        w5500_spi_init();
        ioLibrary_fun_register();

        u8 memsize[2][8] = { {2,2,2,2,2,2,2,2},{2,2,2,2,2,2,2,2}};
        /* wizchip initialize*/
        rtl = ctlwizchip(CW_INIT_WIZCHIP,(void*)memsize);
        if(rtl == -1) {
                LOG_OUT(LOG_ERR "WIZCHIP Initialized fail.\r\n");
                while(1);
        }

        u8 tmp;
        /* PHY link status check */
        do {
                rtl = ctlwizchip(CW_GET_PHYLINK, (void*)&tmp);
                if(rtl == -1) {
                        rtl = 0;                // replace by beep warnning
                        LOG_OUT(LOG_ERR "Unknown PHY Link stauts.\r\n");
                }
        } while(tmp == PHY_LINK_OFF);

        // must be set the default mac before DHCP started.
        setSHAR(w5500_eth_info.mac);

}

void w5500_dhcp_thread(void* param)
{
        u8 dhcp_retry = 0;
        (void)param;
        w5500_init();

        DHCP_init(SOCK_DHCP, w5500_buffer);

        reg_dhcp_cbfunc(w5500_ip_assign, w5500_ip_assign, w5500_ip_conflict);
        while (1) {
                switch(DHCP_run()) {
                case DHCP_IP_ASSIGN:
                case DHCP_IP_CHANGED:
                        goto __final;
                        break;
                case DHCP_FAILED:
                        /* ===== Example pseudo code =====  */
                        // The below code can be replaced your code or omitted.
                        // if omitted, retry to process DHCP
                        dhcp_retry++;
                        if(dhcp_retry > DHCP_RETRY_TIMES) {
                                LOG_OUT(LOG_ERR ">> DHCP %d Failed\r\n", dhcp_retry);
                                dhcp_retry = 0;
                                DHCP_stop();      // if restart, recall DHCP_init()
                                network_init();   // apply the default static network and print out netinfo to serial
                        }
                        break;
                default:
                        break;
                }
        }

__final:
        vTaskDelete(NULL);
}



void w5500_tcp_thread(void* param)
{
        (void)param;
        u8 server_ip[4] = SERVER_IP;			
        while (1) {
                int32_t ret;
                uint16_t size = 0, sentsize=0;
                switch(getSn_SR(SOCK_TCP)) {
                case SOCK_ESTABLISHED :
                        if(getSn_IR(SOCK_TCP) & Sn_IR_CON) {
                                printf("%d:Connected\r\n",SOCK_TCP);
                                setSn_IR(SOCK_TCP,Sn_IR_CON);
                        }
                        
                        if((size = getSn_RX_RSR(SOCK_TCP)) > 0) {
                                if(size > DATA_BUF_SIZE) size = DATA_BUF_SIZE;
                                ret = recv(SOCK_TCP,w5500_buffer,size);
                                if(ret <= 0) printf("ret < 0 \r\n");
                                sentsize = 0;
                                while(size != sentsize) {
                                        ret = send(SOCK_TCP,w5500_buffer + sentsize,size-sentsize);
                                        if(ret < 0) {
                                                close(SOCK_TCP);
                                                printf("ret < 0 \r\n");
                                        }
                                        sentsize += ret; // Don't care SOCKERR_BUSY, because it is zero.
                                }
                        }
                        break;
                case SOCK_CLOSE_WAIT :
                        close(SOCK_TCP);
                        break;
                case SOCK_INIT :													
                        connect(SOCK_TCP, server_ip, SERVER_PORT);			
                        break;
                case SOCK_CLOSED:
                        socket(SOCK_TCP,Sn_MR_TCP,LOCAL_PORT,Sn_MR_ND);
                        break;
                default:
                        break;
                }

        }

}
