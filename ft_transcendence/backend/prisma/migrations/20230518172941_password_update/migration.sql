-- AlterTable
ALTER TABLE "client_stats" ALTER COLUMN "hf" DROP NOT NULL;

-- AlterTable
ALTER TABLE "rooms" ALTER COLUMN "password" SET DATA TYPE TEXT;
