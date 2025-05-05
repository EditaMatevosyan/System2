int lireAdresse(
    int taillePage,
    int tailleMemoireVirtuelle,
    int tailleMemoirePhysique,
    int tablePages[],
    unsigned char memoirePhysique[],
    int adresse,
    unsigned char *pOctet){
        int num_of_vp = tailleMemoireVirtuelle / taillePage;
        int vpn = adresse / taillePage;
        int offset = adresse % taillePage;
        if(vpn >= num_of_vp || vpn < 0)
            return 2;
        int pfn = tablePages[vpn];
        if(pfn == -1)
            return 2;
        int addressPhysique = pfn * taillePage + offset;
        if (addressPhysique >= tailleMemoirePhysique || addressPhysique < 0)
            return 2;
        *pOctet = memoirePhysique[addressPhysique];
        return 0;
    }

    #include <stdio.h>

    int main() {
        int taillePage = 4;
        int tailleMemoireVirtuelle = 64; // 16 pages of 4 bytes
        int tailleMemoirePhysique = 32;  // 8 frames of 4 bytes
    
        // Page Table (size = 16)
        int tablePages[16] = {
            -1, 0x1, -1, -1, 0x6, 0x2, 0x4, 0x0,
            -1, -1, 0x5, 0x7, -1, 0x3, -1, -1
        };
    
        // Physical memory (32 bytes = 8 frames * 4 bytes)
        unsigned char memoirePhysique[32] = {
            // PFN 0x0
            0x6F, 0x34, 0x68, 0xEA,
            // PFN 0x1
            0x05, 0xE2, 0xFA, 0xC8,
            // PFN 0x2
            0x09, 0xED, 0xD4, 0x33,
            // PFN 0x3
            0x39, 0xDF, 0xB8, 0xBE,
            // PFN 0x4
            0xE3, 0x7D, 0xC9, 0xFC,
            // PFN 0x5
            0xCB, 0x7A, 0xF3, 0x49,
            // PFN 0x6
            0x42, 0x1D, 0x7B, 0x41,
            // PFN 0x7
            0xDB, 0x4F, 0x92, 0x03
        };
    
        int adresses[] = {0x07, 0x1F, 0x2B, 0x0D}; // Test addresses
        int nbTests = sizeof(adresses) / sizeof(int);
    
        for (int i = 0; i < nbTests; i++) {
            unsigned char octet;
            int res = lireAdresse(taillePage, tailleMemoireVirtuelle, tailleMemoirePhysique,
                                  tablePages, memoirePhysique, adresses[i], &octet);
            
            printf("Adresse 0x%02X: ", adresses[i]);
            if (res == 0)
                printf("Octet lu = 0x%02X\n", octet);
            else if (res == 1)
                printf("Défaut de page (page fault)\n");
            else if (res == 2)
                printf("Erreur d'accès mémoire (out of bounds)\n");
        }
    
        return 0;
    }